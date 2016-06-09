#pragma once
#include "json.hpp"

class JSONifyable {
    using json = nlohmann::json;

public:
    virtual void fromJson(const json &js) = 0;
    virtual json toJson() const = 0;

    virtual ~JSONifyable(){}
};
