#include "add_to_group_handler.h"
#include "bot.h"
#include "api.h"

void AddToGroupHandler::start(const TgBot::Message::Ptr& message) {
    checkTeacher(message);
    bot_.getApi().sendMessage(message->chat->id, "Введите название группы");
    nextCommand_ = [this](const TgBot::Message::Ptr& message) {
        getGroupName(message);
    };
}

void AddToGroupHandler::getGroupName(const TgBot::Message::Ptr& message) {
    json_["group_id"] = Api::getId("group", "name", message->text);
    bot_.getApi().sendMessage(message->chat->id, "Введите теги новых участников группы через пробел (тег должен начинаться с @)");
    nextCommand_ = [this](const TgBot::Message::Ptr& message) {
        getUserList(message);
    };
}

void AddToGroupHandler::getUserList(const TgBot::Message::Ptr& message) {
    for (const auto& tgUsername : split(message->text)) {
        const auto r = Api::patch("user/" + std::to_string(Api::getId("user", "tg_username", tgUsername.substr(1))), json_);

        if (r.status_code != 200) {
            throw std::runtime_error("Ошибка при добавлении " + tgUsername + ". Операция прервана");
        }
    }

    bot_.getApi().sendMessage(message->chat->id, "Пользователи добавлены в группу");
    nextCommand_ = std::monostate();
}
