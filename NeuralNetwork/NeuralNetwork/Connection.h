#pragma once
#include "jsonifyable.h"

/**
 * @brief Szablon klasy symbolizującej ukierunkowane, ważone połączenie między dwoma obiektami.
 * @tparam T typ obiektu z które z którego połączenie "wychodzi".
 * @tparam U typ obiektu do którego połączenie "wchodzi".
 */
template<typename T, typename U = T>
class Connection : public JSONifyable {
public:
    /**
     * @brief Konstruktor inicjalizujący wszystkie wartości.
     * @param input wskaźnik na obiekt z którego połączenie "wychodzi"
     * @param output wskażnik na obiekt do którego połączenie "wchodzi"
     * @param weight waga połączenia
     */
    Connection(T *input, U *output, double weight) :
        m_input(input),
        m_output(output),
        m_weight(weight),
        m_prevWeight(weight) {
	}

    /**
     * @brief Ustawia wagę połączenia, zapamiętując poprzednią.
     * @param weight nowa waga połączenia.
     */
	void setWeight(double weight){
        m_prevWeight = m_weight;
		m_weight = weight;
	}

    /**
     * @brief Akcesor wagi.
     * @return Aktualna waga połączenia.
     */
	double getWeight() const{
		return m_weight;
	}

    /**
     * @brief Akcesor poprzedniej wagi.
     * @return Poprzednia waga połączenia.
     */
    double getPreviousWeight() const{
        return m_weight;
    }

    /**
     * @brief
     * @return Wskaźnik na obiekt z którego "wychodzi" połączenie.
     */
    T *getInput(){
        return m_input;
    }

    /**
     * @brief
     * @return Wskaźnik na obiekt do którego "wchodzi" połączenie.
     */
    U *getOutput(){
        return m_output;
    }

    /**
     * @brief Stała wersja getInput
     */
    const T *getInput() const{
        return m_input;
    }

    /**
     * @brief Stała wersja getOutput
     */
    const U *getOutput() const{
        return m_output;
    }

    nlohmann::json toJson() const override {
        return {{"weight", getWeight()},
                {"prevWeight", getPreviousWeight()}};
    }

    void fromJson(const nlohmann::json &js) override {
        m_weight = js["weight"];
        m_prevWeight = js["prevWeight"];
    }

private:
    T *m_input;
    U *m_output;
	double m_weight;
    double m_prevWeight;
};
