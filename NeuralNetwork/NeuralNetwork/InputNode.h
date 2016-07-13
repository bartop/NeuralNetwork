#pragma once

#include <vector>
#include "Connection.h"

/**
 * @brief Szablon klasy reprezentującej węzeł wejściowy, łączący obiekt typu U z obiektem typu T.
 *
 * Pozwala utworzyć połączenie do węzła wyjściowego. Przechowuje tablicę swoich połączeń.
 *
 * @warning Klasa nie zwalnia pamięci z utworzonych połączeń!
 *
 * @tparam U klasa obiektu wejściowego.
 * @tparam T klasa obiektu wyjściowego.
 * @tparam Base klasa po której InputNode publicznie dziedziczy. Dzięki temu obiekt może stać się jednocześnie węzłem w grafie.
 */

template<typename U, typename T, typename Base = U>
class InputNode : public Base{
public:
    /**
     * @brief Tworzy połączenie do obiektu destination.
     * @param destination wskaźnik na obiekt do którego tworzone jest połączenie.
     * @tparam O typ obiektu do którego tworzone jest połączenie. Wskaźnik na O musi być niejawnie rzutowalny na wskaźnik na T.
     * @return Wskaźnik do utworzonego połączenia
     */
    template <typename O>
    Connection<U, T> *createConnectionTo(O *destination){
        auto connection = new Connection<U, T>(this, destination, 0);
        m_outputs.push_back(connection);
        destination->addInputConnection(connection);
        return connection;
    }

    /**
     * @brief Tworzy połączenie do obiektu destination.
     * @param destination referencja do obiektu do którego tworzone jest połączenie.
     * @tparam O typ obiektu do którego tworzone jest połączenie. O musi dziedziczyć z T, lub być T.
     * @return Wskaźnik do utworzonego połączenia
     */
    template <typename O>
    Connection<U, T> *createConnectionTo(O &destination){
        return createConnectionTo(&destination);
    }

    /**
     * @brief Dodaje połączenie do tablicy połączeń.
     * @param connection wskaźnik na połączenie między U i T.
     */
    void addOutputConnection(Connection<U, T> *connection){
        m_outputs.push_back(connection);
    }

    /**
     * @brief Pobieranie niemodyfikowalnego wektora połączeń.
     * @return Tablica połączeń wychodzących z tego węzła.
     */
    const std::vector<Connection<U, T> *> &getOutputs() const{ return m_outputs; }

private:
    std::vector<Connection<U, T> *> m_outputs;

};

