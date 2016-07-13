#pragma once
#include <memory>

#include "jsonifyable.h"

/**
 * @brief Wspólny interfejs każdego neurona.
 *
 * Każda klasa reprezentująca neuron musi posiadać wyjście, móc je wyznaczyć oraz być zapisywalna w formacie JSON.
 */
class Neuron : public JSONifyable
{
public:
    /**
     * @brief Pobiera wartość wyjścia neuronu. Funkcja działa w czasie stałym. Aby wyznaczyć wartość wyjścia, należy wywołać metodę calculateOutput.
     * @return Aktualna wartość wyjścia neuronu.
     */
    virtual double getOutput() const = 0;

    /**
     * @brief Oblicza aktualną wartość wyjścia neuronu.
     */
    virtual void calculateOutput() = 0;
    virtual ~Neuron(){}
};
