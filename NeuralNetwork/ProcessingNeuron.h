/*
 * Neuron.h
 *
 *  Created on: 23 mar 2016
 *      Author: Bartosz Miera
 */

#pragma once

#include "Node.h"
#include "Neuron.h"

/**
 * @brief
 *
 */
class ProcessingNeuron: public Node<Neuron> {
public:
    double getOutput() const override;
    void invalidateOutput() override;

private:
	mutable double m_outputValue;
	mutable bool m_valid;

	void countOutput() const;
};
