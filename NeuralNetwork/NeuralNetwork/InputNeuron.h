#pragma once
#include "InputNode.h"
#include "Neuron.h"

class ProcessingNeuron;

/**
 * @brief Klasa reprezentująca neuron z warstwy wejściowej. Przechowuje wartość typu double, która jest jego wyjściem.
 */
class InputNeuron : public InputNode<Neuron, ProcessingNeuron>
{
public:
    /**
     * @brief Konstruktor ustawiający wartość neurono
     * @param value wartość neuronu
     */
    InputNeuron(double value = 0);

    /**
     * @brief Ustawia wartość neuronu
     * @param value nowa wartość
     */
    void setValue(double value);

    /**
     * @brief Zwraca ustawioną wartość wyjścia neuronu.
     * @return ustawiona wartość neuronu
     */
    double getOutput() const override;

    /**
     * @brief Nic nie robi - wyjście jest stałe, nie trzeba go wyliczać.
     */
    void calculateOutput() override;

    void fromJson(const nlohmann::json &) override{}
    nlohmann::json toJson() const override{return nlohmann::json();}

private:
    double m_value;
};

