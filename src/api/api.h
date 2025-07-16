#pragma once

#include <stdint.h>
#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using json = nlohmann::json;

namespace Api {
    cpr::Response get(const std::string& url);
    cpr::Response post(const std::string& url, const json& json);
    cpr::Response patchId(const std::string& url, int id, const json& json);
    cpr::Response delId(const std::string& url, int id);
    cpr::Response getId(const std::string& url, int id, const std::string& method = "");
    cpr::Response postId(const std::string& url, int id, const std::string& method, const json& json);
    
    template<typename T>
    int findId(const std::string& url, const std::string& key, const T& value) {
        const auto list = json::parse(Api::get(url).text);

        for (const auto& id : list) {
            const auto obj = json::parse(Api::getId(url, id).text);
            
            if (obj[key] == value) {
                return id;
            }
        }

        throw std::runtime_error("");
    }
}
