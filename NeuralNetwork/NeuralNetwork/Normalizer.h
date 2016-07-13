#pragma once

#include "loops.hpp"
#include <vector>
#include <stdexcept>

#include "jsonifyable.h"

/**
 * @brief Szablon klasy służącej do normalizacji wartości wektora na podstawie osiągalnych maksimów i minimów.
 * @tparam T typ elementów normalizowanych. Musi być typem arytmetycznym.
 */
template <typename T>
class Normalizer : public JSONifyable{
    std::vector<T> m_min;
    std::vector<T> m_max;

public:
    /**
     * @brief Normalizer konstruktor ustawiający rozmiar.
     * @param size rozmiar normalizowanego wektora.
     */
    Normalizer(std::size_t size):
        m_min(size, 0),
        m_max(size, 1)
    {

    }

    Normalizer() {}

    /**
     * @brief Ustawia wektor minimalnych wartości.
     * @param min wektor możliwych minimów. Rozmiar tego wektora musi być równy rozmiarowi ustawionemu w konstruktorze Normalizera.
     * @throws std::invalid_argument jeśli rozmiar wektora jest nieprawidłowy.
     * @return referencję do samego siebie (*this).
     */
    Normalizer &setMin(const std::vector<T> &min)
    {
        if (min.size() != m_min.size())
        {
            throw std::invalid_argument(std::string("Wrong vector size!\n")
                                              .append(__FILE__)
                                              .append(": ")
                                              .append(std::to_string(__LINE__)));
        }

        m_min = min;
        return *this;
    }


    /**
     * @brief Ustawia wektor maksymalnych wartości.
     * @param min wektor możliwych minimów. Rozmiar tego wektora musi być równy rozmiarowi ustawionemu w konstruktorze Normalizera.
     * @throws std::invalid_argument jeśli rozmiar wektora jest nieprawidłowy.
     * @return referencję do samego siebie (*this).
     */
    Normalizer &setMax(const std::vector<T> &max)
    {
        if (max.size() != m_max.size())
        {
            throw std::invalid_argument(std::string("Wrong vector size!\n")
                                              .append(__FILE__)
                                              .append(": ")
                                              .append(std::to_string(__LINE__)));
        }

        m_max = max;
        return *this;
    }

    /**
     * @brief Normalizuje przekazaną kolekcję zgodnie ze wzorem toNormalize[i] = (toNormalize[i] - min[i])/(max[i] - min[i])
     * @tparam C typ normalizowanego kontenera. Musi zawierać elementy pozwalającę na operacje arytmetyczne z typem T (zwykle typu T).
     * @param toNormalize wektor normalizowany "in place". Jego rozmiaru musi być zgodny z rozmiarem ustawionego w konstruktorze Normalizera.
     * @throws std::invalid_argument jeśli rozmiar wektora jest nieprawidłowy.
     */
    template <typename C>
    void normalize(C &toNormalize)
    {
        if (toNormalize.size() != m_max.size())
        {
            throw std::invalid_argument(std::string("Wrong vector size!\n")
                                        .append(__FILE__)
                                        .append(": ")
                                        .append(std::to_string(__LINE__)));
        }

        std::size_t i = 0;

        for(auto &e : toNormalize)
        {
            e = (e - m_min[i])/(m_max[i] - m_min[i]);
            ++i;
        }
    }

    /**
     * @brief Denormalizuje przekazaną kolekcję zgodnie ze wzorem toDenormalize[i] = toDenormalize[i] * (max[i] - min[i]) + min[i].
     * Przeprowadza operację odwrotną do operacji w metodzie normalize.
     * @tparam C typ normalizowanego kontenera. Musi zawierać elementy pozwalającę na operacje arytmetyczne z typem T (zwykle typu T).
     * @param toDenormalize wektor denormalizowany "in place". Jego rozmiaru musi być zgodny z rozmiarem ustawionego w konstruktorze Normalizera.
     * @throws std::invalid_argument jeśli rozmiar wektora jest nieprawidłowy.
     */
    template <typename C>
    void denormalize(C &toDenormalize)
    {
        if (toDenormalize.size() != m_max.size())
        {
            throw std::invalid_argument(std::string("Wrong vector size!\n")
                                        .append(__FILE__)
                                        .append(": ")
                                        .append(std::to_string(__LINE__)));
        }

        std::size_t i = 0;

        for(auto &e : toDenormalize)
        {
            e = e*(m_max[i] - m_min[i]) + m_min[i];
            ++i;
        }
    }

    nlohmann::json toJson() const override
    {
        return {{"max", m_max},
                {"min", m_min}};
    }

    void fromJson(const nlohmann::json &json) override
    {
        m_max.clear();
        m_min.clear();

        for (const auto &e : json["max"]) {
            m_max.push_back(e.get<double>());
        }

        for (const auto &e : json["min"]) {
            m_min.push_back(e.get<double>());
        }
    }
};
