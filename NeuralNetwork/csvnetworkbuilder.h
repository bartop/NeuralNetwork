#pragma once
#include <utility>
#include <memory>

#include "csvparser.h"
#include "NeuralNetwork/NeuralNetwork.h"
#include "NeuralNetwork/SigmoidNeuron.h"


/**
 * @brief Klasa, której zdaniem jest tworzenie sieci neuronowej z wykorzystaniem danych z pliku CSV oraz ustawionych parametrów.
 *
 * Klasa udostępnia tzw. "fluent api", zgodne z wzorcem projektowym "budowniczy"
 */
class CSVNetworkBuilder {
    double m_inertionRatio;
    CSV::Data m_data;
    unsigned m_previousRows;
    unsigned m_predictedRows;
    unsigned m_processingNeurons;

    std::vector<double> repeat(const std::vector<double> &toRepeat, unsigned times) const;

public:
    /**
     * @brief Ustawia wartość inercji w tworzonej sieci.
     * @param rate wartość inercji
     * @return *this
     */
    CSVNetworkBuilder &setInertion(double rate);

    /**
     * @brief Ustawia dane CSV
     * @param data dane CSV
     * @return *this
     */
    CSVNetworkBuilder &setCSVData(const CSV::Data &data);

    /**
     * @brief Ustawia liczbę rzędów poprzednich
     * @param count liczba rzędów poprzednich
     * @return *this
     */
    CSVNetworkBuilder &setPreviousRows(unsigned count);

    /**
     * @brief Ustawia liczbę rzędów przewidywanych
     * @param count liczba rzędów przewidywanych
     * @return *this
     */
    CSVNetworkBuilder &setPredictedRows(unsigned count);

    /**
     * @brief Ustawia liczbę neuronów warstwy ukrytej.
     * @param count liczba neuronów warstwy ukrytej
     * @return *this
     */
    CSVNetworkBuilder &setProcessingNeuronCount(unsigned count);

    /**
     * @brief Tworzy sieć neuronową na podstawie ustawionych wcześniej parametrów.
     * @return wskaźnik na utworzoną sieć neuronową
     */
    std::unique_ptr<NeuralNetwork<SigmoidNeuron,2>> build() const;

    /**
     * @brief Generuje dane uczące, na podstawie wcześniej ustawionych parametrów.
     * @return parę zawierającą dwie macierze - jedna to wektor kolejnych wektorów wejść sieci, a druga to wektor wektorów odpowiadających, wyjść sieci
     */
    std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>> generateTrainingData();

    /**
     * @brief Zwraca dane CSV z wyfiltrowanymi kolumnami, które nie zawierały wartości liczbowych.
     * @return przefiltrowane dane CSV
     */
    const CSV::Data &getFilteredData() const;
};
