#pragma once
#include "InputNode.h"
#include "Neuron.h"

class InputNeuron : public InputNode<Neuron>
{
public:
    InputNeuron(double value = 0);
    void setValue(double value);

    double getOutput() const override;
    void invalidateOutput() override;

private:
    double m_value;
};

