#pragma once
#include <utility>

#include "csvparser.hpp"
#include "NeuralNetwork/NeuralNetwork.h"
#include "NeuralNetwork/SigmoidNeuron.h"

class CSVNetworkBuilder {
    double m_inertionRatio;
    CSV::Data m_data;
    unsigned m_previousRows;
    unsigned m_predictedRows;
    unsigned m_processingNeurons;

public:
    CSVNetworkBuilder &setInertion(double rate) {
        m_inertionRatio = rate;
        return *this;
    }

    CSVNetworkBuilder &setCSVData(const CSV::Data &data) {
        m_data = &data;

        for (const auto &column : m_data->getColumns()) {
            if (column.isNumeric()) {
                m_data.removeColumn(column.getName());
            }
        }

        return *this;
    }

    CSVNetworkBuilder &setPreviousRows(unsigned count) {
        m_previousRows = count;
        return *this;
    }

    CSVNetworkBuilder &setPredictedRows(unsigned count) {
        m_predictedRows = count;
        return *this;
    }

    CSVNetworkBuilder &setProcessingNeuronCount(unsigned count) {
        m_processingNeurons = count;
        return *this;
    }

    NeuralNetwork<SigmoidNeuron, 2> build() const {
        std::array<unsigned, 3> neurons = {m_previousRows*m_data.getHeader().size(), m_processingNeurons, m_predictedRows*m_data.getHeader().size()};
        NeuralNetwork<SigmoidNeuron, 2> network(neurons, SigmoidNeuron(m_inertionRatio));
        return newtork;
    }

    std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> generateTrainingData()
    {
        std::vector<double> data;
        for (const auto &row : m_data->getRows()) {
            for (const auto &item : row.getItem()) {
                data.push_back(item);
            }
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
                (i < m_predictedRows) && (it != daa.end());
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
};
