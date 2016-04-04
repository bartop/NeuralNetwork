#pragma once
class Neuron
{
public:
    virtual double getOutput() const = 0;
    virtual void invalidateOutput() = 0;
    virtual ~Neuron(){}
};
