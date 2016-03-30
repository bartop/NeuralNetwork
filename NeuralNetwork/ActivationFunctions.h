#pragma once
#include "ActivationFunction.h"


class ActivationFunctions
{
    ActivationFunctions() = delete;

public:
    const static ActivationFunction step;
    const static ActivationFunction linear;
    const static ActivationFunction sigmoid;

};
