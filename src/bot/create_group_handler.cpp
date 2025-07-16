#include "create_group_handler.h"
#include "bot.h"
#include "api.h"

void CreateGroupHandler::start(const TgBot::Message::Ptr& message) {
    checkTeacher(message);
    bot_.getApi().sendMessage(message->chat->id, "Введите название группы");
    nextCommand_ = [this](const TgBot::Message::Ptr& message) {
        getName(message);
    };
}

void CreateGroupHandler::getName(const TgBot::Message::Ptr& message) {
    json_["name"] = message->text;

    if (Api::post("group", json_).status_code != 201) {
        throw std::runtime_error("Ошибка при создании группы");
    }

    bot_.getApi().sendMessage(message->chat->id, "Группа создана");
    nextCommand_ = std::monostate();
}
