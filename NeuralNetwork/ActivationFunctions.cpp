#include "ActivationFunctions.h"
#include <cmath>

const ActivationFunction ActivationFunctions::step(

                             [](double x)->double{
                                return (x > 0) ? 1 : 0;
                              },

                              [](double)->double{
                                return 0.0/0.0;
                              }
                              );

const ActivationFunction ActivationFunctions::linear(
                              [](double x)->double{
                                return x;
                              },

                              [](double)->double{
                                return 1;
                              }
                              );

const ActivationFunction ActivationFunctions::sigmoid(
                              [](double x)->double{
                                return 1.0/(1.0 + std::exp(-x));
                              },

                              [](double x)->double{
                                double ex = std::exp(x);
                                double ex1 = ex + 1;
                                return ex/(ex1*ex1);
                              }
                              );
