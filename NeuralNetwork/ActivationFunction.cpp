#include "ActivationFunction.h"

ActivationFunction::ActivationFunction(std::function<double(double)> function, std::function<double(double)> derivative):
    function(function), functionDerivative(derivative)
{

}

double ActivationFunction::operator()(double x) const
{
    return function(x);
}

double ActivationFunction::derivative(double x) const
{
    return functionDerivative(x);
}
