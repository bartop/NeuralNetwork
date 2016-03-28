/*
 * Neuron.h
 *
 *  Created on: 23 mar 2016
 *      Author: Bartosz Miera
 */

#ifndef NODE_H_
#define NODE_H_

#include <functional>
#include <vector>
#include <utility>
#include "Connection.h"

/**
 * @brief
 *
 */
template<typename Derived>
class Node {
public:
	Connection<Derived> *createConnectionTo(Derived *destination){
		auto connection = new Connection<Derived, Derived>(static_cast<Derived *>(this), destination, 0);
		m_outputs.push_back(connection);
		static_cast<Node<Derived> *>(destination)->addInputConnection(connection);
		return connection;
	}

	Connection<Derived> *createConnectionFrom(Derived *source){
		auto connection = new Connection<Derived, Derived>(source, static_cast<Derived *>(this), 0);
		m_outputs.push_back(connection);
		static_cast<Node<Derived> *>(source)->addOutputConnection(connection);
		return connection;
	}

	void addInputConnection(Connection<Derived> *connection){
		m_inputs.push_back(connection);
	}

	void addOutputConnection(Connection<Derived> *connection){
		m_outputs.push_back(connection);
	}

	const std::vector<Connection<Derived, Derived> *> &getInputs() const { return m_inputs; }
	const std::vector<Connection<Derived, Derived> *> &getOutputs() const{ return m_outputs; }

private:
	std::vector<Connection<Derived, Derived> *> m_inputs;
	std::vector<Connection<Derived, Derived> *> m_outputs;

};

#endif /* NODE_H_ */
