/*
 * Connection.h
 *
 *  Created on: 23 mar 2016
 *      Author: Bartosz Miera
 */

#pragma once

/**
 * @brief
 *
 */
template<typename T, typename U = T>
class Connection {
public:
	Connection(T *input, U *output, double weight){
		m_input = input;
		m_output = output;
		m_weight = weight;
	}

	void setWeight(double weight){
		m_weight = weight;
	}

	double getWeight() const{
		return m_weight;
	}

	const T *getInput() const{
		return m_input;
	}

	const U *getOutput() const{
		return m_output;
	}

private:
	const T *m_input;
	const U *m_output;
	double m_weight;
};
