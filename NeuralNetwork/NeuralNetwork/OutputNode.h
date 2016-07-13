#pragma once

#include <vector>
#include "Connection.h"

/**
 * @brief Szablon klasy reprezentującej węzeł wyjściowy, łączący obiekt typu U z obiektem typu T.
 *
 * Pozwala utworzyć połączenie z węzła wejściowego. Przechowuje tablicę swoich połączeń.
 *
 * @warning Klasa nie zwalnia pamięci z utworzonych połączeń!
 *
 * @tparam U klasa obiektu wejściowego.
 * @tparam T klasa obiektu wyjściowego.
 * @tparam Base klasa po której InputNode publicznie dziedziczy. Dzięki temu obiekt może stać się jednocześnie węzłem w grafie.
 */
template<typename U, typename T, typename Base = T>
class OutputNode : public Base {
public:
    /**
     * @brief Tworzy połączenie z obiektu source.
     * @param source wskaźnik na obiekt z którego tworzone jest połączenie.
     * @tparam I typ obiektu do którego tworzone jest połączenie. Wskaźnik na I musi być niejawnie rzutowalny na wskaźnik na U.
     * @return Wskaźnik do utworzonego połączenia
     */
    template <typename I>
    Connection<U, T> *createConnectionFrom(I *source){
        auto connection = new Connection<U, T>(source, this, 0);
        m_inputs.push_back(connection);
        source->addOutputConnection(connection);
        return connection;
    }

    /**
     * @brief Tworzy połączenie z obiektu source.
     * @param source referencja do obiektu z którego tworzone jest połączenie.
     * @tparam O typ obiektu do którego tworzone jest połączenie. I musi dziedziczyć z U, lub być U.
     * @return Wskaźnik do utworzonego połączenia
     */
    template <typename I>
    Connection<U, T> *createConnectionFrom(I &source){
        return createConnectionFrom(&source);
    }


    /**
     * @brief Dodaje połączenie do tablicy połączeń.
     * @param connection wskaźnik na połączenie między U i T.
     */
    void addInputConnection(Connection<U, T> *connection){
        m_inputs.push_back(connection);
    }

    /**
     * @brief Pobieranie niemodyfikowalnego wektora połączeń.
     * @return Tablica połączeń wychodzących z tego węzła.
     */
    const std::vector<Connection<U, T> *> &getInputs() const { return m_inputs; }

private:
    std::vector<Connection<U, T> *> m_inputs;
};
