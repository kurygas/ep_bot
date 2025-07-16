#include "api.h"
#include "config.h"

cpr::Response Api::get(const std::string& url) {
    return cpr::Get(
        cpr::Url{Config::apiUrl + url},
        cpr::Bearer{Config::apiToken},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Timeout{5000}
    );
}

cpr::Response Api::post(const std::string& url, const json& json) {
    return cpr::Post(
        cpr::Url{Config::apiUrl + url},
        cpr::Bearer{Config::apiToken},
        cpr::Body{json.dump()},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Timeout{5000}
    );
}

cpr::Response Api::delId(const std::string& url, const int id) {
    return cpr::Delete(
        cpr::Url{std::format("{}{}/{}", Config::apiUrl, url, std::to_string(id))},
        cpr::Bearer{Config::apiToken},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Timeout{5000}
    );
}

cpr::Response Api::getId(const std::string& url, const int id, const std::string& method) {
    auto path = std::format("{}{}/{}/", Config::apiUrl, url, std::to_string(id));

    if (method.empty()) {
        path.pop_back();
    }
    else {
        path += method;
    }

    return cpr::Get(
        cpr::Url{path},
        cpr::Bearer{Config::apiToken},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Timeout{5000}
    );
}

cpr::Response Api::postId(const std::string& url, const int id, const std::string& method, const json& json) {
    return cpr::Post(
        cpr::Url{std::format("{}{}/{}/{}", Config::apiUrl, url, std::to_string(id), method)},
        cpr::Bearer{Config::apiToken},
        cpr::Body{json.dump()},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Timeout{5000}
    );
}

cpr::Response Api::patchId(const std::string& url, const int id, const json& json) {
    return cpr::Patch(
        cpr::Url{std::format("{}{}/{}", Config::apiUrl, url, std::to_string(id))},
        cpr::Bearer{Config::apiToken},
        cpr::Body{json.dump()},
        cpr::Header{{"Content-Type", "application/json"}},
        cpr::Timeout{5000}
    );
}
