/*
 * NeuralNetwork.cpp
 *
 *  Created on: 30 mar 2016
 *      Author: Bartosz Miera
 */

#include "NeuralNetwork.h"
#include "ActivationFunctions.h"

std::vector<double> NeuralNetwork::feedForward(
		const std::vector<double>& inputData) {
	for (int i = 0; i < inputData.size(); ++i) {
		m_inputLayer[i]->setValue(inputData[i]);
	}

	std::vector<double> result;
	for(auto i : *m_layers.rend()){
		result.push_back(i->getOutput());
	}
	return result;
}

void NeuralNetwork::backPropagate(const std::vector<double>& inputData,
		const std::vector<double>& expectedResult) {
	std::vector<double> results = feedForward(inputData);
	//TODO complete
}

NeuralNetwork::NeuralNetwork(const std::vector<unsigned>& topology) {
	//create input layer
	for (int i = 0; i < topology[0]; ++i) {
		m_inputLayer.push_back(new InputNeuron(0));
	}
	//create hidden and output layers
	for (int i = 1; i < topology.size(); ++i) {
		std::vector<ProcessingNeuron *> layer;
		for (int j = 0; j < topology[i]; ++j) {
			layer.push_back(new ProcessingNeuron(ActivationFunctions::sigmoid));
		}
		m_layers.push_back(layer);
	}
	//create connections from input layer
	for (int i = 0; i < topology[0]; ++i) {
		for (int j = 0; j < topology[1]; ++j) {
			m_connections.push_back(m_inputLayer[i]->createConnectionTo(m_layers[0][j]));
		}
	}
	//create connections between hidden layers
	for (int i = 1; i < topology.size(); ++i) {
		for (int j = 0; j < topology[i - 1]; ++j) {
			for (int k = 0; k < topology[i]; ++k) {
				m_connections.push_back(m_layers[i - 1][j]->createConnectionTo(m_layers[i][k]));
			}
		}
	}
	//create bias neurons - one for each layer except final one
	for (int i = 0; i < topology.size() - 1; ++i) {
		m_biasNeurons.push_back(new InputNeuron(1));
		//add connections from bias
		for (int j = 0; j < topology[i + 1]; ++j) {
			m_connections.push_back(m_biasNeurons[i]->createConnectionTo(m_layers[i][j]));
		}
	}
}

NeuralNetwork::~NeuralNetwork() {
	for(auto i : m_connections){
		delete i;
	}

	for(auto i : m_biasNeurons){
		delete i;
	}

	for(auto i : m_inputLayer){
		delete i;
	}

	for(auto i : m_layers){
		for(auto j : i){
			delete j;
		}
	}
}

