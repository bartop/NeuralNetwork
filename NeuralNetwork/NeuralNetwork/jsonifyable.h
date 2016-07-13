#pragma once
#include "json.hpp"

/**
 * @brief Interfejs klasy serializowalnej i deserializowalnej z formatu JSON.
 */
class JSONifyable {
    using json = nlohmann::json;

public:
    /**
     * @brief Deserializacja z formatu JSON.
     * @param js obiekt nlohmann::json z którego stan obiektu jest odczytywany.
     */
    virtual void fromJson(const json &js) = 0;

    /**
     * @brief Serializacja do formatu JSON.
     * @return obiekt nlohmann::json z odpowiednio zapisanym stanem obiektu.
     */
    virtual json toJson() const = 0;

    virtual ~JSONifyable(){}
};
