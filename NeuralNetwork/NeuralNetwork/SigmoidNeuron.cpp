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

void SigmoidNeuron::fromJson(const nlohmann::json &json)
{
    m_inertionRatio = json["inertionRatio"];
    m_multiplier = json["multiplier"];
}

nlohmann::json SigmoidNeuron::toJson() const
{
    nlohmann::json json = {{"inertionRatio", m_inertionRatio},
                           {"multiplier", m_multiplier}};
    return json;
}

SigmoidNeuron::SigmoidNeuron(double inertionRatio, double multiplier):
    m_inertionRatio(inertionRatio),
    m_multiplier(multiplier)
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
        double prevChange = con->getWeight() - con->getPreviousWeight();
        double change = rate * ( (1.0 - m_inertionRatio) * m_delta * con->getInput()->getOutput() +
                                 m_inertionRatio * prevChange);
        con->setWeight(con->getWeight() + change);
    }
}
