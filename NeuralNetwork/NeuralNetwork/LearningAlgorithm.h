#pragma once
#include "NeuralNetworkI.h"
#include <atomic>
#include <limits>

class LearningAlgorithm
{
    NeuralNetworkI *m_network;
    std::atomic_bool m_stop = false;
    float m_progress = 0;
    double m_avarageError = std::numeric_limits<double>::max();

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

    double getCurrentError() const {
        return m_avarageError;
    }


    void learn(const std::vector<std::vector<double>> &inputs,
               const std::vector<std::vector<double>> &expectedOutputs,
               double rate = 0.5,
               unsigned repeat = 1)
    {
        m_progress = 0.f;
        for (unsigned k = 0; k < repeat; ++k)
        {
            double avarageError = 0.f;

            for (unsigned i = 0; i < inputs.size(); ++i)
            {
                m_network->setInput(inputs[i]);
                m_network->calculateOutput();
                m_network->backPropagate(expectedOutputs[i]);
                m_network->updateWeights(rate);

                avarageError += meanSquareError(expectedOutputs[i]);
            }
            avarageError /= inputs.size();
            m_avarageError = avarageError;
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
