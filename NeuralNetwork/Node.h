/*
 * Neuron.h
 *
 *  Created on: 23 mar 2016
 *      Author: Bartosz Miera
 */

#pragma once

#include "InputNode.h"
#include "OutputNode.h"

/**
 * @brief
 *
 */
template<typename Base>
class Node : public InputNode<Base>, public OutputNode<Base>
{

};
