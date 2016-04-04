/*
 * Neuron.cpp
 *
 *  Created on: 23 mar 2016
 *      Author: Bartosz Miera
 */

#include "SigmoidNeuron.h"
#include "Connection.h"
#include "ActivationFunctions.h"

void SigmoidNeuron::countOutput() const{
    m_count = 0;
    for(auto i : getInputs()){
        m_count +=
                i->getInput()->getOutput() *
                i->getWeight();
    }
}

void SigmoidNeuron::applyActivationFunction() const
{
    m_outputValue = m_activationFunction(m_count);
}

void SigmoidNeuron::calculateDelta()
{
    double sum = 0;

    for (auto &con : getOutputs())
    {
        sum += con->getOutput()->getDelta() * con->getWeight();
    }

    m_delta = m_activationFunction.derivative(m_count) * sum;
}

void SigmoidNeuron::calculateDelta(double expected)
{
    m_delta = m_activationFunction.derivative(m_count) * (expected - getOutput());

}

SigmoidNeuron::SigmoidNeuron() :
    m_activationFunction(ActivationFunctions::sigmoid)
{

}


double SigmoidNeuron::getOutput() const {
    if(!m_valid)
    {
        countOutput();
        applyActivationFunction();

        m_valid = true;
    }

    return m_outputValue;
}

void SigmoidNeuron::invalidateOutput() {
    m_valid = false;

    for (auto &con: getInputs())
    {
        con->getInput()->invalidateOutput();
    }
}


double SigmoidNeuron::getDelta() const
{
    return m_delta;
}

void SigmoidNeuron::updateWeights(double rate)
{
    for (auto &con : getInputs())
    {
        con->setWeight(con->getWeight() + rate * m_delta * con->getInput()->getOutput());
    }
}
