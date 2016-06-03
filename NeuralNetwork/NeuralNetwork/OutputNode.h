#pragma once

#include <vector>


/**
 * @brief
 *
 */
template<typename U, typename T, typename Base = T>
class OutputNode : public Base {
public:
    template <typename I>
    Connection<U, T> *createConnectionFrom(I *source){
        auto connection = new Connection<U, T>(source, this, 0);
        m_inputs.push_back(connection);
        source->addOutputConnection(connection);
        return connection;
    }

    template <typename I>
    Connection<U, T> *createConnectionFrom(I &source){
        return createConnectionFrom(&source);
    }

    void addInputConnection(Connection<U, T> *connection){
        m_inputs.push_back(connection);
    }

    const std::vector<Connection<U, T> *> &getInputs() const { return m_inputs; }

private:
    std::vector<Connection<U, T> *> m_inputs;
};

/*
template<typename T, typename Base, bool inherit = true>
class OutputNode : public OutputNodeBase<T, Base, Base>{


};

template<typename T, typename Base>
class OutputNode<T, Base, false> : public OutputNodeBase<T, Base, __Dummy>
{

};*/
