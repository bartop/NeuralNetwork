#pragma once

#include <vector>
#include "Connection.h"

/**
 * @brief
 *
 */

template<typename U, typename T, typename Base = U>
class InputNode : public Base{
public:
    template <typename O>
    Connection<U, T> *createConnectionTo(O *destination){
        auto connection = new Connection<U, T>(this, destination, 0);
        m_outputs.push_back(connection);
        destination->addInputConnection(connection);
        return connection;
    }

    template <typename O>
    Connection<U, T> *createConnectionTo(O &destination){
        return createConnectionTo(&destination);
    }

    void addOutputConnection(Connection<U, T> *connection){
        m_outputs.push_back(connection);
    }

    const std::vector<Connection<U, T> *> &getOutputs() const{ return m_outputs; }

private:
    std::vector<Connection<U, T> *> m_outputs;

};

/*
template<typename Base, typename T = Base, bool inherit = true>
class InputNode : public InputNodeBase<Base, T, Base>{


};


template<typename Base, typename T>
class InputNode<Base, T, false> : public InputNodeBase<Base, T, __Dummy>
{

};
*/

