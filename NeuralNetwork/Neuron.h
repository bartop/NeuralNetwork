#pragma once
class Neuron
{
public:
    virtual double getOutput() const = 0;
    virtual void calculateOutput() = 0;
    virtual ~Neuron(){}
};
