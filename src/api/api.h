#pragma once

#include <stdint.h>
#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>

using json = nlohmann::json;

namespace Api {
    cpr::Response get(const std::string& url, const json& json = json());
    cpr::Response post(const std::string& url, const json& json = json());
    cpr::Response patch(const std::string& url, const json& json = json());
    cpr::Response del(const std::string& url, const json& json = json());
    
    template<typename T>
    int getId(const std::string& url, const std::string& key, const T& value) {
        auto r = Api::get(url);

        if (r.status_code != 200) {
            throw std::runtime_error("");
        }

        for (const auto& id : json::parse(r.text)["list"].get<std::vector<int>>()) {
            r = Api::get(url + '/' + std::to_string(id));
            
            if (r.status_code == 200 && json::parse(r.text)[key].get<T>() == value) {
                return id;
            }
        }

        throw std::runtime_error("");
    }
}
