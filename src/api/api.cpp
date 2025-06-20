#include "api.h"
#include "config.h"

cpr::Response Api::get(const std::string& url, const json& json) {
    return cpr::Get(
        cpr::Url{Config::apiUrl + url},
        cpr::Bearer{Config::apiToken},
        cpr::Body{json.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );
}

cpr::Response Api::post(const std::string& url, const json& json) {
    return cpr::Post(
        cpr::Url{Config::apiUrl + url},
        cpr::Bearer{Config::apiToken},
        cpr::Body{json.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );
}

cpr::Response Api::del(const std::string& url, const json& json) {
    return cpr::Delete(
        cpr::Url{Config::apiUrl + url},
        cpr::Bearer{Config::apiToken},
        cpr::Body{json.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );
}

cpr::Response Api::patch(const std::string& url, const json& json) {
    return cpr::Patch(
        cpr::Url{Config::apiUrl + url},
        cpr::Bearer{Config::apiToken},
        cpr::Body{json.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );
}
