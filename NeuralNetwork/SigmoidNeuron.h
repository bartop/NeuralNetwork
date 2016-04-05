/*
 * Neuron.h
 *
 *  Created on: 23 mar 2016
 *      Author: Bartosz Miera
 */

#pragma once

#include <memory>

#include "Node.h"
#include "ProcessingNeuron.h"
#include "ActivationFunction.h"

/**
 * @brief
 *
 */
class SigmoidNeuron: public Node<Neuron, ProcessingNeuron> {
public:
    SigmoidNeuron(double multiplier = 1.0);
    double getOutput() const override;
    void calculateOutput() override;

    double getDelta() const override;
    void updateWeights(double rate) override;

    void calculateDelta();
    void calculateDelta(double expected);

private:
    double m_multiplier;
    double m_delta;
    double m_outputValue;

    double activationFunction(double x) const;
    double outputDerivative() const;
};
