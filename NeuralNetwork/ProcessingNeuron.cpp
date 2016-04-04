/*
 * Neuron.cpp
 *
 *  Created on: 23 mar 2016
 *      Author: Bartosz Miera
 */

#include "ProcessingNeuron.h"
#include "Connection.h"

void ProcessingNeuron::countOutput() const{
    m_count = 0;
	for(auto i : getInputs()){
        m_count +=
				i->getInput()->getOutput() *
				i->getWeight();
    }
}

void ProcessingNeuron::applyActivationFunction() const
{
    m_outputValue = m_activationFunction(m_count);
}

void ProcessingNeuron::calculateDelta()
{
    double sum = 0;
    
    for (auto &con : getOutputs())
    {
        sum += con->getOutput()->getDelta() * con->getWeight();
    }
    
    m_delta = m_activationFunction.derivative(m_count) * sum;
}

void ProcessingNeuron::calculateDelta(double expected)
{
    m_delta = m_activationFunction.derivative(m_count) * (getOutput() - expected);

}

ProcessingNeuron::ProcessingNeuron(const ActivationFunction &activationFunction) :
    m_activationFunction(activationFunction)
{

}


double ProcessingNeuron::getOutput() const {
    if(!m_valid)
    {
        countOutput();
        applyActivationFunction();

        m_valid = true;
    }

	return m_outputValue;
}

void ProcessingNeuron::invalidateOutput() {
    m_valid = false;

    for (auto &con: getInputs())
    {
        con->getInput()->invalidateOutput();
    }
}

Eigen::VectorXd ProcessingNeuron::getInputWeights() const
{
    auto inputs = getInputs();
    Eigen::VectorXd inputWeights(inputs.size());
    for (unsigned i = 0; i < inputs.size(); ++i)
    {
        inputWeights(i) = inputs[i]->getWeight();
    }

    return inputWeights;
}

void ProcessingNeuron::setInputWeights(const Eigen::VectorXd &inputWeights)
{
    for (unsigned i = 0; i < getInputs().size(); ++i)
    {
        getInputs()[i]->setWeight(inputWeights(i));
    }
}

double ProcessingNeuron::getDelta() const
{
    return m_delta;
}

void ProcessingNeuron::updateWeights(double rate)
{
    for (auto &con : getInputs())
    {
        con->setWeight(con->getWeight() - rate * m_delta * con->getInput()->getOutput());
    }
}
