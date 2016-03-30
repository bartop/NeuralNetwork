#pragma once

#include <vector>
#include "Connection.h"

template<typename Derived>
class OutputNode;

/**
 * @brief
 *
 */
template<typename Base>
class InputNode : public virtual Base {
public:
    Connection<Base> *createConnectionTo(OutputNode<Base> *destination){
        auto connection = new Connection<Base>(this, destination, 0);
        m_outputs.push_back(connection);
        destination->addInputConnection(connection);
        return connection;
    }

    Connection<Base> *createConnectionTo(OutputNode<Base> &destination){
        return createConnectionTo(&destination);
    }

    void addOutputConnection(Connection<Base> *connection){
        m_outputs.push_back(connection);
    }

    const std::vector<Connection<Base> *> &getOutputs() const{ return m_outputs; }

private:
    std::vector<Connection<Base> *> m_outputs;

};

