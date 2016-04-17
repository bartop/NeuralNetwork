#pragma once
#include <array>
#include <vector>
#include <memory>
#include <random>
#include <cmath>
#include <neuralnetworki.h>
#include <initializer_list>

#include "InputNeuron.h"
#include "helper.h"

template <class NeuronClass, unsigned PROCESSING_LAYERS_COUNT>
class NeuralNetwork : public NeuralNetworkI
{
    static_assert(PROCESSING_LAYERS_COUNT > 0, "Network needs to have at least one processing layer!");
    InputNeuron m_biasNeuron;
    std::array<std::vector<NeuronClass>, PROCESSING_LAYERS_COUNT> m_processingLayers;
    std::vector<InputNeuron> m_inputLayer;
    std::vector<std::unique_ptr<Connection<Neuron, ProcessingNeuron>>> m_connections;
    std::vector<double> m_outputMultiplier, m_outputOffset;

    template <typename F>
    void foreachProcessingNeuron(F function)
    {
        for (auto &layer : m_processingLayers)
        {
            for (auto &neuron : layer)
            {
                function(neuron);
            }
        }
    }

    template <typename InputLayer, typename OutputLayer>
    void connectLayers(InputLayer &inputLayer, OutputLayer &outputLayer)
    {
        for (auto &outputNeuron : outputLayer)
        {
            m_connections.push_back(
                        std::unique_ptr<Connection<Neuron, ProcessingNeuron>>(
                            outputNeuron.createConnectionFrom(&m_biasNeuron)));

            for (auto &inputNeuron : inputLayer)
            {
                m_connections.push_back(
                            std::unique_ptr<Connection<Neuron, ProcessingNeuron>>(
                                inputNeuron.createConnectionTo(&outputNeuron)));
            }
        }
    }

    template <typename Layer>
    void randomizeWeights(Layer &layer)
    {
        std::random_device rd;
        std::mt19937 gen(rd());

        for (auto &neuron : layer)
        {
            double inputsSqrt = std::sqrt((double)neuron.getInputs().size());
            double max = 1/inputsSqrt;
            double min = -max;
            std::uniform_real_distribution<> dis(min, max);

            for (auto &con : neuron.getInputs())
            {
                con->setWeight(dis(gen));
            }
        }
    }

    /*template <unsigned i = 0, typename... T>
    void initialize(T first, T...args)
    {
        randomizeWeights(m_processingLayers);
    }

    template <unsigned i, typename T>
    void initialize(T first)
    {
        static_assert( i != PROCESSING_LAYERS_COUNT - 1, "Wrong number of initializers");
        m_processingLayers.resize(first);
        randomizeWeights(m_processingLayers[i]);
        connectLayers(m_processingLayers[i - 1], m_processingLayers[i]);
    }

    template <unsigned i, typename T>
    void initialize<0, T>(T first)
    {
        randomizeWeights(m_processingLayers[i]);
        connectLayers(m_inputLayer, m_processingLayers[i]);
    }*/

public:
    NeuralNetwork(const std::initializer_list<unsigned> &neuronsInLayers) :
        m_biasNeuron(1.0)
    {
        //static_assert(neuronsInLayers.size() == PROCESSING_LAYERS_COUNT + 1, "Wrong size!");
        auto it = neuronsInLayers.begin();
        m_inputLayer.resize(*it);

        for (auto &vec : m_processingLayers)
        {
            vec.resize(*(++it));
        }

        connectLayers(m_inputLayer, m_processingLayers[0]);
        randomizeWeights(m_processingLayers[0]);

        for (unsigned i = 0; i < PROCESSING_LAYERS_COUNT - 1; ++i)
        {
            connectLayers(m_processingLayers[i], m_processingLayers[i+1]);
            randomizeWeights(m_processingLayers[i+1]);
        }

        m_outputMultiplier.resize(m_processingLayers.back().size(), 1.0);
        m_outputOffset.resize(m_processingLayers.back().size(), 0.0);

    }

    void calculateOutput() override
    {
        foreachProcessingNeuron([](auto &neuron){neuron.calculateOutput();});
    }

    std::vector<double> getOutput() override
    {
        std::vector<double> output;
        calculateOutput();

        for (const auto &neuron : m_processingLayers.back())
        {
            output.push_back(neuron.getOutput());
        }

        output = (output  * m_outputMultiplier) - m_outputOffset;

        return output;
    }

    void setInput(const std::vector<double> &inputs) override
    {
        auto it = inputs.begin();
        for (InputNeuron &neuron : m_inputLayer)
        {
            neuron.setValue(*(it++));
        }
    }

    void backPropagate(const std::vector<double> &expectedOutput) override
    {
        std::vector<double> scaled = (expectedOutput + m_outputOffset) / m_outputMultiplier;
        auto expected = scaled.begin();
        for (auto &neuron : m_processingLayers.back())
        {
            neuron.calculateDelta(*expected);
            ++expected;
        }

        for (auto it = std::next(m_processingLayers.rbegin());
             it < m_processingLayers.rend();
             ++it)
        {
            for (auto &neuron : *it)
            {
                neuron.calculateDelta();
            }
        }
    }

    void setOutputMultiplier(const std::vector<double> &outputMultiplier) override
    {
        m_outputMultiplier = outputMultiplier;
    }

    void setOutputOffset(const std::vector<double> &offset)
    {
        m_outputOffset = offset;
    }


    void updateWeights(double learningRate) override
    {
        foreachProcessingNeuron([learningRate](auto &neuron){neuron.updateWeights(learningRate);});
    }

    constexpr unsigned processingLayers() const
    {
        return PROCESSING_LAYERS_COUNT;
    }

    const std::vector<NeuronClass> &getProcessingLayer(unsigned number) const
    {
        return m_processingLayers[number];
    }

    const std::vector<InputNeuron> &getInputLayer() const
    {
        return m_inputLayer;
    }


};
