#include "api.h"
#include "request.h"

bool Api::userExist(const int64_t tgId) {
    auto r = Request::get("user/");

    if (r.status_code != 200) {
        throw std::runtime_error("api error");
    }

    auto json = json::parse(r.text);

    for (const auto& userId : json["user_list"].get<std::vector<int64_t>>()) {
        r = Request::get("user/" + std::to_string(userId));
        json = json::parse(r.text);

        if (r.status_code == 200 && json["tg_id"].get<int64_t>() == tgId) {
            return true;
        }
    }

    return false;
}

void Api::registerUser(const json& payload) {
    if (Request::post("user/", payload).status_code != 201) {
        throw std::runtime_error("");
    }
}

void Api::createGroup(const json& payload) {
    if (Request::post("group/", payload).status_code != 201) {
        throw std::runtime_error("");
    }
}

bool Api::isUserTeacher(const int userId) {
    
}
