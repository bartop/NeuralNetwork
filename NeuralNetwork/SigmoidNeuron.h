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
    SigmoidNeuron();
    double getOutput() const override;
    void invalidateOutput() override;

    double getDelta() const override;
    void updateWeights(double rate) override;

    void calculateDelta();
    void calculateDelta(double expected);


private:
    const ActivationFunction &m_activationFunction;

    mutable double m_count;
    double m_delta;
    mutable double m_outputValue;
    mutable bool m_valid;

    void countOutput() const;
    void applyActivationFunction() const;
};
