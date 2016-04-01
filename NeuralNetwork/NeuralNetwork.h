/*
 * NeuralNetwork.h
 *
 *  Created on: 30 mar 2016
 *      Author: Bartosz Miera
 */

#pragma once

#include "InputNeuron.h"
#include "Neuron.h"
#include "Connection.h"

/**
 * @brief
 *
 */
class NeuralNetwork {
public:
	NeuralNetwork(const std::vector<unsigned> &topology);
	std::vector<double> feedForward(const std::vector<double> &inputData);
	void backPropagate(const std::vector<double> &inputData,
			const std::vector<double> &expectedResult);
	~NeuralNetwork();

private:
	std::vector<InputNeuron *> m_inputLayer;
	std::vector<InputNeuron *> m_biasNeurons;
	std::vector<std::vector<ProcessingNeuron *> > m_layers;
	std::vector<Connection<Neuron> *> m_connections;
};
