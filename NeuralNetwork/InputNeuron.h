#pragma once
#include "InputNode.h"
#include "Neuron.h"

class ProcessingNeuron;

class InputNeuron : public InputNode<Neuron, ProcessingNeuron>
{
public:
    InputNeuron(double value = 0);
    void setValue(double value);

    double getOutput() const override;
    void calculateOutput() override;

private:
    double m_value;
};

