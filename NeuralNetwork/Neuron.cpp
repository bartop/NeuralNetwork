/*
 * Neuron.cpp
 *
 *  Created on: 23 mar 2016
 *      Author: Bartosz Miera
 */

#include "Neuron.h"
#include "Connection.h"

void Neuron::countOutput() const{
	m_valid = true;
	m_outputValue = 0;
	for(auto i : getInputs()){
		m_outputValue +=
				i->getInput()->getOutput() *
				i->getWeight();
	}
}

double Neuron::getOutput() const {
	if(!m_valid) countOutput();
	return m_outputValue;
}

void Neuron::invalidateOutput() {
	m_valid = false;
}
