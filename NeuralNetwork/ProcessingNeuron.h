/*
 * Neuron.h
 *
 *  Created on: 23 mar 2016
 *      Author: Bartosz Miera
 */

#pragma once

#include <memory>

#include "Node.h"
#include "Neuron.h"
#include "ActivationFunction.h"

/**
 * @brief
 *
 */
class ProcessingNeuron: public Node<Neuron> {
public:
    ProcessingNeuron(const ActivationFunction &activationFunction);
    double getOutput() const override;
    void invalidateOutput() override;

private:
    const ActivationFunction &m_activationFunction;

	mutable double m_outputValue;
	mutable bool m_valid;

	void countOutput() const;
    void applyActivationFunction() const;
};
