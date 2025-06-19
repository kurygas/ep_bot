#pragma once

#include "config.h"

#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using json = nlohmann::json;

namespace Request {
    cpr::Response get(const std::string& url, const json& json = json());
    cpr::Response post(const std::string& url, const json& json = json());
    cpr::Response patch(const std::string& url, const json& json = json());
    cpr::Response del(const std::string& url, const json& json = json());

    void checkStatusCode(int code);
}
