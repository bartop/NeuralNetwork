#pragma once
#include <memory>

#include "jsonifyable.h"

class Neuron : public JSONifyable
{
public:
    virtual double getOutput() const = 0;
    virtual void calculateOutput() = 0;
    virtual ~Neuron(){}
};
