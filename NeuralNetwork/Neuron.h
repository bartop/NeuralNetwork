/*
 * Neuron.h
 *
 *  Created on: 23 mar 2016
 *      Author: Bartosz Miera
 */

#ifndef NEURON_H_
#define NEURON_H_

#include "Node.h"

/**
 * @brief
 *
 */
class Neuron: public Node<Neuron> {
public:
	double getOutput() const;
	void invalidateOutput();

private:
	mutable double m_outputValue;
	mutable bool m_valid;

	void countOutput() const;
};

#endif /* NEURON_H_ */
