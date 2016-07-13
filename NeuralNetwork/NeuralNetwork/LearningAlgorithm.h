#pragma once
#include "NeuralNetworkI.h"
#include <atomic>
#include <limits>

class LearningAlgorithm
{
    NeuralNetworkI *m_network;
    std::atomic_bool m_stop{false};
    float m_progress = 0;
    double m_avarageError = std::numeric_limits<double>::max();

public:
    LearningAlgorithm(NeuralNetworkI &network) : m_network(&network)
    {

    }
    
    void stop() {
        m_stop = true;
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
        unsigned errorUpdateRate = (repeat * 0.01) + 1; //błąd liczony co 1% postępu
        m_progress = 0.f;
        m_stop = false;
        for (unsigned k = 0; k < repeat && !m_stop; ++k)
        {
            double avarageError = 0.f;

            for (unsigned i = 0; i < inputs.size() && !m_stop; ++i)
            {
                m_network->setInput(inputs[i]);
                m_network->calculateOutput();
                m_network->backPropagate(expectedOutputs[i]);
                m_network->updateWeights(rate);

                if (k % errorUpdateRate == 0)
                {
                    avarageError += meanSquareError(expectedOutputs[i]);
                }
            }

            if (k % errorUpdateRate == 0)
            {
                m_avarageError = avarageError/inputs.size();
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
        m_stop = false;
        while (repeat && !m_stop)
        {
            repeat = false;
            double avarageError = 0;
            for (unsigned i = 0; i < inputs.size() && !m_stop; ++i)
            {
                m_network->setInput(inputs[i]);
                m_network->calculateOutput();
                m_network->backPropagate(expectedOutputs[i]);
                m_network->updateWeights(rate);

                double error = meanSquareError(expectedOutputs[i]);
                avarageError += error;

                if (error > desiredError)
                {
                    repeat = true;
                }
            }
            m_avarageError = avarageError/inputs.size();
        }
    }

};
