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

    void fromJson(const nlohmann::json &) override{}
    nlohmann::json toJson() const override{return nlohmann::json();}

private:
    double m_value;
};

