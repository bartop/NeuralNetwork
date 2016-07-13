#pragma once
#include <vector>
#include "jsonifyable.h"

class NeuralNetworkI : public JSONifyable
{
public:
    /**
     * @brief Oblicza wyjście sieci na podstawie ustawionego wejścia
     */
    virtual void calculateOutput() = 0;

    /**
     * @brief
     * @return Wektory wyjść neuronów warstwy wyjściowej
     */
    virtual std::vector<double> getOutput() = 0;

    /**
     * @brief Ustawia wejście sieci.
     * @param inputs wektor wejść. Powinien mieć rozmiar równy liczbie neuronów wejściowych.
     */
    virtual void setInput(const std::vector<double> &inputs) = 0;

    /**
     * @brief Propaguje wcześniej przekazany błąd.
     * @param expectedOutput oczekiwane wyjście dla wcześniej ustawionego wejścia sieci.
     */
    virtual void backPropagate(const std::vector<double> &expectedOutput) = 0;

    /**
     * @brief Aktualizacj wszystkich wag połączeń.
     * @param learningRate współczynnik uczenia wykorzystywany przy aktualizaci.
     */
    virtual void updateWeights(double learningRate) = 0;
    virtual ~NeuralNetworkI(){}
};
