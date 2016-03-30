#pragma once

#include <vector>
#include "Connection.h"

template<typename T>
class InputNode;

/**
 * @brief
 *
 */
template<typename Base>
class OutputNode : public virtual Base {
public:
    Connection<Base> *createConnectionFrom(InputNode<Base> *source){
        auto connection = new Connection<Base>(source, this, 0);
        m_inputs.push_back(connection);
        source->addOutputConnection(connection);
        return connection;
    }

    Connection<Base> *createConnectionFrom(InputNode<Base> &source){
        return createConnectionFrom(&source);
    }

    void addInputConnection(Connection<Base> *connection){
        m_inputs.push_back(connection);
    }

    const std::vector<Connection<Base> *> &getInputs() const { return m_inputs; }

private:
    std::vector<Connection<Base> *> m_inputs;
};
