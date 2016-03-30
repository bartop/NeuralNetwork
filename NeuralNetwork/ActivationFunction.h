#pragma once
#include <functional>

class ActivationFunction
{
    std::function<double(double)> function;
    std::function<double(double)> functionDerivative;

public:
    ActivationFunction(std::function<double(double)> function, std::function<double(double)> derivative);
    double operator()(double x) const;
    double derivative(double x) const;
};

