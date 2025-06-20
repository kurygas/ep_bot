#include "create_group_handler.h"
#include "bot.h"
#include "api.h"

CreateGroupHandler::CreateGroupHandler(Bot& bot, const TgBot::Message::Ptr& message)
: CommandHandler(bot) {
    checkTeacher(message);
    bot_.getApi().sendMessage(message->chat->id, "Введите название группы");
    nextCommand_ = [this](const TgBot::Message::Ptr& message) {
        getName(message);
    };
}

void CreateGroupHandler::getName(const TgBot::Message::Ptr& message) {
    json_["name"] = message->text;

    if (Api::post("group", json_).status_code != 201) {
        throw std::runtime_error("");
    }

    bot_.getApi().sendMessage(message->chat->id, "Группа создана");
}
