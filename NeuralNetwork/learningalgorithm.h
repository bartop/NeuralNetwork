#pragma once
#include "neuralnetwork.h"

template <typename NeuronClass, unsigned LAYERS>
class LearningAlgorithm
{
    NeuralNetwork<NeuronClass, LAYERS> &m_network;

public:
    LearningAlgorithm(NeuralNetwork<NeuronClass, LAYERS> &network) : m_network(network)
    {

    }

    double meanSquareError(const std::vector<double> &expected)
    {
        auto it = expected.begin();
        double sum = 0;

        for (double output : m_network.getOutput())
        {
            sum += std::pow(output - *(it++), 2.0);
        }

        return sum/expected.size();
    }

    void learn(const std::vector<std::vector<double>> &inputs,
               const std::vector<std::vector<double>> &expectedOutputs,
               double rate = 0.05,
               unsigned repeat = 1)
    {
        for (unsigned k = 0; k < repeat; ++k)
        {
            for (unsigned i = 0; i < inputs.size(); ++i)
            {
                m_network.setInput(inputs[i]);
                m_network.calculateOutput();
                m_network.backPropagate(expectedOutputs[i]);
                m_network.updateWeights(rate);
            }
        }
    }

};
