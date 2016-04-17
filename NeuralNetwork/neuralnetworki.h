#pragma once
#include <vector>

class NeuralNetworkI
{
public:
    virtual void setOutputMultiplier(const std::vector<double> &outputMultiplier) = 0;
    virtual void calculateOutput() = 0;
    virtual std::vector<double> getOutput() = 0;
    virtual void setInput(const std::vector<double> &inputs) = 0;
    virtual void backPropagate(const std::vector<double> &expectedOutput) = 0;
    virtual void updateWeights(double learningRate) = 0;

};
