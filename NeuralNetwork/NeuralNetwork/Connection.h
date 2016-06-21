/*
 * Connection.h
 *
 *  Created on: 23 mar 2016
 *      Author: Bartosz Miera
 */

#pragma once
#include "jsonifyable.h"

/**
 * @brief
 *
 */
template<typename T, typename U = T>
class Connection : public JSONifyable {
public:
    Connection(T *input, U *output, double weight){
		m_input = input;
		m_output = output;
		m_weight = weight;
	}

	void setWeight(double weight){
        m_prevWeight = m_weight;
		m_weight = weight;
	}

	double getWeight() const{
		return m_weight;
	}

    double getPreviousWeight() const{
        return m_weight;
    }

    T *getInput(){
        return m_input;
    }

    U *getOutput(){
        return m_output;
    }

    const T *getInput() const{
        return m_input;
    }

    const U *getOutput() const{
        return m_output;
    }

    nlohmann::json toJson() const override {
        return {{"weight", getWeight()},
                {"prevWeight", getPreviousWeight()}};
    }

    void fromJson(const nlohmann::json &js) override {
        m_weight = js["weight"];
        m_prevWeight = js["prevWeight"];
    }

private:
    T *m_input;
    U *m_output;
	double m_weight;
    double m_prevWeight;
};