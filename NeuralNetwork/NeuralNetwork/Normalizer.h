#pragma once

#include "loops.hpp"
#include <vector>
#include <stdexcept>

#include "jsonifyable.h"

template <typename T>
class Normalizer : public JSONifyable{
    std::vector<T> m_min;
    std::vector<T> m_max;

public:
    Normalizer(std::size_t size):
        m_min(size, 0),
        m_max(size, 1)
    {

    }

    Normalizer()
    {

    }

    Normalizer &setMin(const std::vector<T> &min)
    {
        if (min.size() != m_min.size())
        {
            throw std::invalid_argument("Wrong vector size!");
        }

        m_min = min;
        return *this;
    }

    Normalizer &setMax(const std::vector<T> &max)
    {
        if (max.size() != m_max.size())
        {
            throw std::invalid_argument("Wrong vector size!");
        }

        m_max = max;
        return *this;
    }

    template <typename C>
    void normalize(C &toNormalize)
    {
        if (toNormalize.size() != m_max.size())
        {
            throw std::invalid_argument("Wrong vector size!");
        }

        std::size_t i = 0;

        for(auto &e : toNormalize)
        {
            e = (e - m_min[i])/(m_max[i] - m_min[i]);
            ++i;
        }
    }

    template <typename C>
    void denormalize(C &toDenormalize)
    {
        if (toDenormalize.size() != m_max.size())
        {
            throw std::invalid_argument("Wrong vector size!");
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
