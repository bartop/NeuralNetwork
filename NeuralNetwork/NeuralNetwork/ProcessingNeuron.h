#pragma once

#include "Neuron.h"

/**
 * @brief Interfejs neuronu warstw ukrytych i warstwy wyjściowej, pozwalający na wykorzystanie metody wstecznej propagacji błędu.
 *
 */
class ProcessingNeuron: public Neuron {
public:
    /**
     * @brief Wartość potrzebna do wstecznej propagacji błędu,
     * @return Wartość wcześniej wyznaczonej delty.
     */
    virtual double getDelta() const = 0;

    /**
     * @brief Uaktualnia wagi połączeń wejściowych, wykorzystując poprzednio obliczoną wartość delty.
     * @param rate współczynnik uczenia.
     */
    virtual void updateWeights(double rate) = 0;

    /**
     * @brief Wyznacza wartość delty.
     */
    virtual void calculateDelta() = 0;

    /**
     * @brief Wyznacza wartość delty. Wyorzystywana w warstwie wyjściowej.
     * @param expected oczekiwana wartość wyjścia, w stosunku do wyjścia aktualnie obliczonego.
     */
    virtual void calculateDelta(double expected) = 0;

    virtual ~ProcessingNeuron(){}
};
