/*
 * Neuron.cpp
 *
 *  Created on: 23 mar 2016
 *      Author: Bartosz Miera
 */

#include "SigmoidNeuron.h"
#include "Connection.h"
#include <cmath>

double SigmoidNeuron::activationFunction(double x) const
{
     return 1.0/(1.0 + std::exp(-x*m_multiplier));
}

double SigmoidNeuron::outputDerivative() const
{
    return (getOutput())*(1.0 - getOutput())*m_multiplier;
}

void SigmoidNeuron::calculateDelta()
{
    double sum = 0;

    for (auto &con : getOutputs())
    {
        sum += con->getOutput()->getDelta() * con->getWeight();
    }

    m_delta = outputDerivative() * sum;
}

void SigmoidNeuron::calculateDelta(double expected)
{
    m_delta = outputDerivative() * (expected - getOutput());

}

SigmoidNeuron::SigmoidNeuron(double multiplier):m_multiplier(multiplier)
{

}


double SigmoidNeuron::getOutput() const {
    return m_outputValue;
}

void SigmoidNeuron::calculateOutput() {
    m_outputValue = 0;
    for(auto i : getInputs()){
        m_outputValue +=
                i->getInput()->getOutput() *
                i->getWeight();
    }

    m_outputValue = activationFunction(m_outputValue);

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
