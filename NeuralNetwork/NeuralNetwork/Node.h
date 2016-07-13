#pragma once

#include "InputNode.h"
#include "OutputNode.h"

/**
 * @brief Węzeł wejściowy i wyjściowy jednocześni.
 * @tparam T typ obiektu wejściowego w grafie.
 * @tparam U typ obiektu wyjściowego w grafie. Node pośrednio dziedziczy po U.
 */
template<typename T, typename U = T>
class Node : public InputNode<T, U, OutputNode<T, U>>
{

};
