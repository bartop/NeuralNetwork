#pragma once
#include "NeuralNetworkI.h"
#include <atomic>
#include <limits>

/**
 * @brief Klasa realizująca proces uczenia sieci neuronowej.
 *
 * Klasa może być używana wielowątkowo, przy czym to klient klasy jest odpowiedzialny za zarządzanie wątkami.
 */
class LearningAlgorithm
{
    NeuralNetworkI *m_network;
    std::atomic_bool m_stop{false};
    std::atomic<float> m_progress {0};
    std::atomic<double> m_avarageError {std::numeric_limits<double>::max()};

public:
    /**
     * @brief Konstuktor przyjmujący referencję na uczoną sieć.
     * @param network referencja na uczoną sieć, obiekt sieci musi żyć dłużej niż obiekt algorytmu uczącego
     */
    explicit LearningAlgorithm(NeuralNetworkI &network);
    
    /**
     * @brief Przerywa proces uczenia, przydatne, jeśli metody uczące zostały wywołane w osobnym wątku.
     */
    void stop();

    /**
     * @brief Zwraca aktualny postęp procesu uczenia, przydatne przy wykorzystaniu wielowątkowym.
     * @return wartość procentowa postępu
     */
    float getProgress() const;

    /**
     * @brief Zwraca błąd średniokwadratowy dla podanych oczekiwanych wyjść i obecnego stanu sieci.
     * @param expected oczekiwane wyjścia
     * @return Błąd średniokwadratowy ze wszystkich wyjść sieci
     */
    double meanSquareError(const std::vector<double> &expected);

    /**
     * @brief Zwraca obecny, średni błąd średniokwadratowy. Przydatne przy wykorzystaniu wielowątkowym.
     * @return średni błąd średniokwadratowy w poprzedniej epoce
     */
    double getCurrentError() const;


    /**
     * @brief Metoda odpowiadająca za proces uczenia o stałej liczbie epok.
     * @param inputs wektor wejść sieci
     * @param expectedOutputs wektor oczekiwanych wyjść sieci
     * @param rate współczynnik uczenia
     * @param repeat liczba powtórzeń (epok)
     */
    void learn(const std::vector<std::vector<double>> &inputs,
               const std::vector<std::vector<double>> &expectedOutputs,
               double rate = 0.5,
               unsigned repeat = 1);

    /**
     * @brief Metoda odpowiadająca za proces uczenia, aż do osiągnięcia zadanego błędu.
     * @param inputs wektor wejść sieci
     * @param expectedOutputs wektor oczekiwanych wyjść sieci
     * @param rate współczynnik uczenia
     * @param desiredError oczekiwany błąd
     */
    void learnUntilError(const std::vector<std::vector<double>> &inputs,
               const std::vector<std::vector<double>> &expectedOutputs,
               double rate,
               double desiredError);

};
