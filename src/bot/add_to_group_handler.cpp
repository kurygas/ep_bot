#include "add_to_group_handler.h"
#include "bot.h"
#include "api.h"

AddToGroupHandler::AddToGroupHandler(Bot& bot, const TgBot::Message::Ptr& message)
: CommandHandler(bot) {
    checkTeacher(message);
    bot_.getApi().sendMessage(message->chat->id, "Введите название группы");
    nextCommand_ = [this](const TgBot::Message::Ptr& message) {
        getGroupName(message);
    };
}

void AddToGroupHandler::getGroupName(const TgBot::Message::Ptr& message) {
    json_["group_id"] = Api::getId("group", "name", message->text);
    bot_.getApi().sendMessage(message->chat->id, "Введите теги новых участниокв группы через пробел (тег должен начинаться с @)");
    nextCommand_ = [this](const TgBot::Message::Ptr& message) {
        getUserList(message);
    };
}

void AddToGroupHandler::getUserList(const TgBot::Message::Ptr& message) {
    for (const auto& tgUsername : split(message->text)) {
        Api::patch("user" + Api::getId("user", "tg_username", tgUsername), json_);
    }

    bot_.getApi().sendMessage(message->chat->id, "Пользователи добавлены в группу");
    finished_ = true;
}
