#pragma once
#include <vector>
#include <fstream>
#include <utility>

class WeatherDataReader
{
    static unsigned constexpr ColumnsPerRow = 6;
    static unsigned constexpr RowsPerDay = 2;
    std::vector<std::vector<double>> m_data;

    std::vector<std::vector<double>> m_outputs;
    std::vector<std::vector<double>> m_inputs;



public:
    using IOPair = std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>>;

    WeatherDataReader(const std::string &filePath);

    IOPair generateTrainingData(unsigned prevDays, unsigned predictedDays);
};

