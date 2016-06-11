#pragma once
#include "NeuralNetworkI.h"

class LearningAlgorithm
{
    NeuralNetworkI *m_network;
    float m_progress = 0;

public:
    LearningAlgorithm(NeuralNetworkI &network) : m_network(&network)
    {

    }

    float getProgress() const {
        return m_progress;
    }

    double meanSquareError(const std::vector<double> &expected)
    {
        auto it = expected.begin();
        double sum = 0;

        for (double output : m_network->getOutput())
        {
            sum += std::pow(output - *(it++), 2.0);
        }

        return sum/expected.size();
    }

    void learn(const std::vector<std::vector<double>> &inputs,
               const std::vector<std::vector<double>> &expectedOutputs,
               double rate = 0.5,
               unsigned repeat = 1)
    {
        m_progress = 0.f;
        for (unsigned k = 0; k < repeat; ++k)
        {
            for (unsigned i = 0; i < inputs.size(); ++i)
            {
                m_network->setInput(inputs[i]);
                m_network->calculateOutput();
                m_network->backPropagate(expectedOutputs[i]);
                m_network->updateWeights(rate);
            }

            m_progress = float(k)/(repeat);
        }
        m_progress = 1;
    }

    void learnUntilError(const std::vector<std::vector<double>> &inputs,
               const std::vector<std::vector<double>> &expectedOutputs,
               double rate,
               double desiredError)
    {
        bool repeat = true;
        while (repeat)
        {
            repeat = false;
            for (unsigned i = 0; i < inputs.size(); ++i)
            {
                m_network->setInput(inputs[i]);
                m_network->calculateOutput();
                m_network->backPropagate(expectedOutputs[i]);
                m_network->updateWeights(rate);

                if (meanSquareError(expectedOutputs[i]) > desiredError)
                {
                    repeat = true;
                }
            }
        }
    }

};
