/*
 * Neuron.h
 *
 *  Created on: 23 mar 2016
 *      Author: Bartosz Miera
 */

#pragma once

#include "Neuron.h"


/**
 * @brief
 *
 */
class ProcessingNeuron: public virtual Neuron {
public:
    virtual double getDelta() const = 0;
    virtual void updateWeights(double rate) = 0;
    virtual ~ProcessingNeuron(){}
};
