#include "create_semester_handler.h"
#include "bot.h"
#include "api.h"

void CreateSemesterHandler::start(const TgBot::Message::Ptr& message) {
    checkTeacher(message);
    bot_.getApi().sendMessage(message->chat->id, "Введите номер семестра");
    nextCommand_ = [this](const TgBot::Message::Ptr& message) {
        getSemesterNumber(message);
    };
}

void CreateSemesterHandler::getSemesterNumber(const TgBot::Message::Ptr& message) {
    json_["semester_number"] = std::stoi(message->text);
    bot_.getApi().sendMessage(message->chat->id, "Выберите предмет", nullptr, nullptr, createSubjectKeyboard());
    nextCommand_ = [this](const TgBot::CallbackQuery::Ptr& callbackQuery) {
        getSubject(callbackQuery);
    };
}

void CreateSemesterHandler::getSubject(const TgBot::CallbackQuery::Ptr& callbackQuery) {
    json_["subject"] = std::stoi(callbackQuery->data);
    bot_.getApi().sendMessage(callbackQuery->message->chat->id, "Укажите дату начала семестра в формате дд.мм.гггг");
    nextCommand_ = [this](const TgBot::Message::Ptr& message) {
        getStart(message);
    };
}

void CreateSemesterHandler::getStart(const TgBot::Message::Ptr& message) {
    const auto data = split(message->text, '.');
    json_["start"] = getTime(std::stoi(data[0]), std::stoi(data[1]), std::stoi(data[2]));
    bot_.getApi().sendMessage(message->chat->id, "Укажите дату конца семестра в формате дд.мм.гггг");
    nextCommand_ = [this](const TgBot::Message::Ptr& message) {
        getEnd(message);
    };
}

void CreateSemesterHandler::getEnd(const TgBot::Message::Ptr& message) {
    const auto data = split(message->text, '.');
    json_["end"] = getTime(std::stoi(data[0]), std::stoi(data[1]), std::stoi(data[2]));
    const auto groups = json::parse(Api::get("group").text);
    std::vector<std::pair<std::string, std::string>> keyboardData;

    for (const auto& groupId : groups) {
        const auto group = json::parse(Api::getId("group", groupId).text);
        bool goodGroup = true;
        
        if (group.contains("semester_list")) {
            for (const auto& semesterId : group["semester_list"]) {
                const auto semester = json::parse(Api::getId("semester", semesterId).text);
                
                if (semester["subject"] == json_["subject"] && semester["semester_number"] == json_["semester_number"]) {
                    goodGroup = false;
                }
            }
        }

        if (goodGroup) {
            keyboardData.emplace_back(group["name"], std::to_string(static_cast<int>(groupId)));
        }
    }

    if (keyboardData.empty()) {
        throw std::runtime_error("Подходящих групп не существует");
    }

    bot_.getApi().sendMessage(message->chat->id, "Выберите группу", nullptr, nullptr, createKeyboard(keyboardData));
    nextCommand_ = [this](const TgBot::CallbackQuery::Ptr& callbackQuery) {
        getGroupId(callbackQuery);
    };
}

void CreateSemesterHandler::getGroupId(const TgBot::CallbackQuery::Ptr& callbackQuery) {
    json_["group_id"] = std::stoi(callbackQuery->data);

    if (Api::post("semester", json_).status_code != 201) {
        throw std::runtime_error("Ошибка при создании семестнра");
    }

    bot_.getApi().sendMessage(callbackQuery->message->chat->id, "Семестр создан");
    nextCommand_ = std::monostate();
}
