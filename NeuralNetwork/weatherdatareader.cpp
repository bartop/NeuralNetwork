#include "weatherdatareader.h"

WeatherDataReader::WeatherDataReader(const std::string &filePath)
{
    std::ifstream file(filePath);

    while (file)
    {
        std::vector<double> row;
        double temp;
        std::string date, time;

        //not used
        file >> date;
        file >> time;

        for (unsigned j = 0; j < ColumnsPerRow - 1; ++j)
        {
            file >> temp;
            row.push_back(temp);
        }

        m_data.push_back(row);
        row.clear();
    }
}

WeatherDataReader::IOPair WeatherDataReader::generateTrainingData(unsigned prevDays, unsigned predictedDays)
{
    std::vector<std::vector<double>> inputs;
    std::vector<std::vector<double>> outputs;

    auto it = m_data.begin();

    std::vector<double> row;

    while (it != m_data.end())
    {
        for(unsigned i = 0;
            (i < prevDays*RowsPerDay) && (it != m_data.end());
            (++i, ++it))
        {
            row.insert(row.end(), it->begin(), it->end());
        }

        if (!row.empty())
            inputs.push_back(row);
        row.clear();

        for(unsigned i = 0;
            (i < predictedDays*RowsPerDay) && (it != m_data.end());
            (++i, ++it))
        {
            row.insert(row.end(), it->begin(), it->end());
        }

        if (!row.empty())
            outputs.push_back(row);
        row.clear();

        if (it != m_data.end())
        {
            it -= (prevDays + predictedDays - 1)*RowsPerDay;
        }
    }

    if (inputs.size() > outputs.size())
    {
        inputs.pop_back();
    }

    return std::make_pair(inputs, outputs);
}


