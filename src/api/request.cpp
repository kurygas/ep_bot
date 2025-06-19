#include "request.h"

#include <iostream>

cpr::Response Request::get(const std::string& url, const json& json) {
    const auto r = cpr::Get(
        cpr::Url{Config::apiUrl + url},
        cpr::Bearer{Config::apiToken},
        cpr::Body{json.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );
    checkStatusCode(r.status_code);
    return r;
}

cpr::Response Request::post(const std::string& url, const json& json) {
    const auto r = cpr::Post(
        cpr::Url{Config::apiUrl + url},
        cpr::Bearer{Config::apiToken},
        cpr::Body{json.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );
    checkStatusCode(r.status_code);
    return r;
}

cpr::Response Request::del(const std::string& url, const json& json) {
    const auto r = cpr::Delete(
        cpr::Url{Config::apiUrl + url},
        cpr::Bearer{Config::apiToken},
        cpr::Body{json.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );
    checkStatusCode(r.status_code);
    return r;
}

cpr::Response Request::patch(const std::string& url, const json& json) {
    const auto r = cpr::Patch(
        cpr::Url{Config::apiUrl + url},
        cpr::Bearer{Config::apiToken},
        cpr::Body{json.dump()},
        cpr::Header{{"Content-Type", "application/json"}}
    );
    checkStatusCode(r.status_code);
    return r;
}

void Request::checkStatusCode(const int code) {
    if (code != 200 || code != 201 || code != 204) {
        throw std::runtime_error("");
    }
}
