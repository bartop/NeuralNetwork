#include "csvnetworkbuilder.h"



std::vector<double> CSVNetworkBuilder::repeat(const std::vector<double> &toRepeat, unsigned times) const
{
    std::vector<double> result;

    for (unsigned i = 0; i < times; ++i)
    {
        for (double element : toRepeat)
        {
            result.push_back(element);
        }
    }

    return result;
}

CSVNetworkBuilder &CSVNetworkBuilder::setInertion(double rate) {
    m_inertionRatio = rate;
    return *this;
}

CSVNetworkBuilder &CSVNetworkBuilder::setCSVData(const CSV::Data &data) {
    m_data = data;

    for (const auto &column : m_data.getColumns()) {
        if (!column.isNumeric()) {
            m_data.removeColumn(column.getName());
        }
    }

    return *this;
}

CSVNetworkBuilder &CSVNetworkBuilder::setPreviousRows(unsigned count) {
    m_previousRows = count;
    return *this;
}

CSVNetworkBuilder &CSVNetworkBuilder::setPredictedRows(unsigned count) {
    m_predictedRows = count;
    return *this;
}

CSVNetworkBuilder &CSVNetworkBuilder::setProcessingNeuronCount(unsigned count) {
    m_processingNeurons = count;
    return *this;
}

std::unique_ptr<NeuralNetwork<SigmoidNeuron,2>> CSVNetworkBuilder::build() const {
    std::array<unsigned, 3> neurons = {m_previousRows*m_data.getHeader().size(),
                                       m_processingNeurons,
                                       m_predictedRows*m_data.getHeader().size()};
    std::unique_ptr<NeuralNetwork<SigmoidNeuron, 2>> network{new NeuralNetwork<SigmoidNeuron,2>(neurons, SigmoidNeuron(m_inertionRatio))};

    std::vector<double> min;
    std::vector<double> max;

    for (const auto &column : m_data.getColumns()) {
        auto minmax = std::minmax_element(column.getItems().begin(),
                                          column.getItems().end(),
                                          [](const CSV::Item &r, const CSV::Item &l) {
            return double(r) < double(l);
        });
        min.push_back(*minmax.first - std::fabs(*minmax.second)*0.25);
        max.push_back(*minmax.second + std::fabs(*minmax.second)*0.25);
    }

    network->getInputNormalizer().setMin(repeat(min, m_previousRows));
    network->getInputNormalizer().setMax(repeat(max, m_previousRows));

    network->getOutputNormalizer().setMin(repeat(min, m_predictedRows));
    network->getOutputNormalizer().setMax(repeat(max, m_predictedRows));

    return network;
}

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> CSVNetworkBuilder::generateTrainingData()
{
    std::vector<std::vector<double>> data;
    for (const auto &row : m_data.getRows()) {
        std::vector<double> r;
        for (const auto &item : row.getItems()) {
            r.push_back(item);
        }
        data.push_back(r);
    }

    std::vector<std::vector<double>> inputs;
    std::vector<std::vector<double>> outputs;

    auto it = data.begin();

    std::vector<double> row;

    while (it != data.end())
    {
        for(unsigned i = 0;
            (i < m_previousRows) && (it != data.end());
            (++i, ++it))
        {
            row.insert(row.end(), it->begin(), it->end());
        }

        if (!row.empty())
            inputs.push_back(row);
        row.clear();

        for(unsigned i = 0;
            (i < m_predictedRows) && (it != data.end());
            (++i, ++it))
        {
            row.insert(row.end(), it->begin(), it->end());
        }

        if (!row.empty())
            outputs.push_back(row);
        row.clear();

        if (it != data.end())
        {
            it -= (m_previousRows + m_predictedRows - 1);
        }
    }

    if (inputs.size() > outputs.size())
    {
        inputs.pop_back();
    }

    return std::make_pair(inputs, outputs);
}

const CSV::Data &CSVNetworkBuilder::getFilteredData() const
{
    return m_data;
}
