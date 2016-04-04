#include "InputNeuron.h"

InputNeuron::InputNeuron(double value)
{
    setValue(value);
}

void InputNeuron::setValue(double value)
{
    m_value = value;
}

double InputNeuron::getOutput() const
{
    return m_value;
}

void InputNeuron::invalidateOutput()
{
    //do nothing...
}
