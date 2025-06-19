#pragma once

#include <stdint.h>
#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace Api {
    bool userExist(int64_t tgId);
    void registerUser(const json& payload);
    void createGroup(const json& payload);
    bool isUserTeacher(int userId);
}
