#pragma once

#include <string>

namespace Config {
    inline std::string apiUrl;
    inline std::string botToken;
    inline std::string apiToken;

    void setConfigs();
}
