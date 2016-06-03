#pragma once
#include <array>
#include <vector>
#include <memory>
#include <random>
#include <cmath>
#include <initializer_list>

#include "NeuralNetworkI.h"
#include "InputNeuron.h"
#include "helper.h"
#include "json.hpp"
#include "Normalizer.h"
#include <range/v3/all.hpp>

using namespace ranges;

template <class NeuronClass, unsigned PROCESSING_LAYERS_COUNT>
class NeuralNetwork : public NeuralNetworkI
{
    using json = nlohmann::json;

    static_assert(PROCESSING_LAYERS_COUNT > 0, "Network needs to have at least one processing layer!");
    InputNeuron m_biasNeuron;
    NeuronClass m_prototype;
    std::array<std::vector<NeuronClass>, PROCESSING_LAYERS_COUNT> m_processingLayers;
    std::vector<InputNeuron> m_inputLayer;
    std::vector<std::unique_ptr<Connection<Neuron, ProcessingNeuron>>> m_connections;
    //std::vector<double> m_outputMultiplier, m_outputOffset, m_inputMultiplier, m_inputOffset;
    Normalizer<double> m_inputNormalizer, m_outputNormalizer;

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

    template <typename Iter>
    void reinitialize(Iter begin, Iter end)
    {
        m_biasNeuron = InputNeuron(1.0);
        m_connections.clear();

        auto it = begin;
        m_inputLayer.resize(*it);


        for (auto &vec : m_processingLayers)
        {
            vec.resize(*(++it), m_prototype);
        }

        connectLayers(m_inputLayer, m_processingLayers[0]);
        randomizeWeights(m_processingLayers[0]);

        for (unsigned i = 0; i < PROCESSING_LAYERS_COUNT - 1; ++i)
        {
            connectLayers(m_processingLayers[i], m_processingLayers[i+1]);
            randomizeWeights(m_processingLayers[i+1]);
        }

        m_inputNormalizer = Normalizer<double>(m_inputLayer.size());
        m_outputNormalizer = Normalizer<double>(m_processingLayers.back().size());
    }

public:
    NeuralNetwork(const std::array<unsigned, PROCESSING_LAYERS_COUNT + 1> &neuronsInLayers) : NeuralNetwork(neuronsInLayers, NeuronClass())
    {
    }

    NeuralNetwork(const std::array<unsigned, PROCESSING_LAYERS_COUNT + 1> &neuronsInLayers, const NeuronClass &prototype) :
        m_biasNeuron(1.0), m_prototype(prototype), m_inputNormalizer(neuronsInLayers.front()), m_outputNormalizer(neuronsInLayers.back())
    {
        reinitialize(neuronsInLayers.begin(), neuronsInLayers.end());
    }

    NeuralNetwork(const json &network)
    {
        fromJson(network);
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

        m_outputNormalizer.denormalize(output);

        return output;
    }

    void setInput(const std::vector<double> &inputs) override
    {
        auto normalizedInputs = inputs;
        m_inputNormalizer.normalize(normalizedInputs);
        auto it = normalizedInputs.begin();

        for (InputNeuron &neuron : m_inputLayer)
        {
            neuron.setValue(*(it++));
        }
    }

    void backPropagate(const std::vector<double> &expectedOutput) override
    {
        std::vector<double> scaled = expectedOutput;
        m_outputNormalizer.normalize(scaled);
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

    Normalizer<double> &getInputNormalizer() {
        return m_inputNormalizer;
    }

    Normalizer<double> &getOutputNormalizer() {
        return m_outputNormalizer;
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

    json toJson() const
    {

        json network;
        network["layersSize"].push_back(m_inputLayer.size());

        for (const auto &layer : m_processingLayers)
        {
            network["layersSize"].push_back(layer.size());
        }

        for (const auto &connection : m_connections)
        {
            network["connections"].push_back(connection->toJson());
        }

        network["inputNormalizer"] = m_inputNormalizer.toJson();
        network["outputNormalizer"] = m_outputNormalizer.toJson();

        for (std::size_t i = 0; i < m_processingLayers.size(); ++i)
        {
            for (std::size_t j = 0; j < m_processingLayers[i].size(); ++j)
            {
                network["layer"][i][j] = m_processingLayers[i][j].toJson();
            }
        }
        return network;
    }

    void fromJson(const json &network)
    {
        reinitialize(network["layersSize"].begin(), network["layersSize"].end());

        auto it = network["connections"].begin();

        for (auto &connection : m_connections)
        {
            connection->fromJson(*(it++));
        }

        m_inputNormalizer.fromJson(network["inputNormalizer"]);
        m_outputNormalizer.fromJson(network["outputNormalizer"]);

        for (std::size_t i = 0; i < m_processingLayers.size(); ++i)
        {
            for (std::size_t j = 0; j < m_processingLayers[i].size(); ++j)
            {
                m_processingLayers[i][j].fromJson(network["layer"][i][j]);
            }
        }
    }
};
