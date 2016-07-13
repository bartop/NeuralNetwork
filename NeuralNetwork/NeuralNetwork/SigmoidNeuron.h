/*
 * Neuron.h
 *
 *  Created on: 23 mar 2016
 *      Author: Bartosz Miera
 */

#pragma once

#include <memory>

#include "Node.h"
#include "ProcessingNeuron.h"
#include "json.hpp"

/**
 * @brief Klasa reprezentująca neuron z funkcją aktywacji typu sigmoid. Implementuje interfejs ProcessingNeuron. Jest też węzłem łączącym Nueron z ProcessingNeuron.
 *
 */
class SigmoidNeuron: public Node<Neuron, ProcessingNeuron> {
public:
    /**
     * @brief Konstruktor ustawiający parametry.
     * @param inertialRatio współczynnik inercji, 0 to brak inercji, 1 to maksymalna inercja.
     * @param multiplier mnożnik funkcji aktywacji
     */
    SigmoidNeuron(double inertialRatio = 0.0, double multiplier = 1.0);
    SigmoidNeuron(const SigmoidNeuron &sigmoid) = default;
    SigmoidNeuron(SigmoidNeuron &&sigmoid) = default;

    double getOutput() const override;
    void calculateOutput() override;

    double getDelta() const override;
    void updateWeights(double rate) override;

    void calculateDelta() override;
    void calculateDelta(double expected) override;

    SigmoidNeuron &operator=(const SigmoidNeuron &) = default;
    SigmoidNeuron &operator=(SigmoidNeuron &&) = default;

    void fromJson(const nlohmann::json &json) override;
    nlohmann::json toJson() const override;

private:
    double m_inertionRatio;
    double m_multiplier;
    double m_delta;
    double m_outputValue;


    double activationFunction(double x) const;
    double outputDerivative() const;
};
