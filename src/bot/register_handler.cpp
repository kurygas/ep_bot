#include "register_handler.h"
#include "bot.h"
#include "api.h"

RegisterHandler::RegisterHandler(Bot& bot, const TgBot::Message::Ptr& message)
: CommandHandler(bot) {
    json_["tg_id"] = message->from->id;
    json_["tg_username"] = message->from->username;
    bot_.getApi().sendMessage(message->chat->id, "Введите вашу фамилию (на кириллице)");
    nextCommand_ = [this](const TgBot::Message::Ptr& message) {
        getSurname(message);
    };
}

void RegisterHandler::getName(const TgBot::Message::Ptr& message) {
    json_["name"] = message->text;
    const auto r = Api::post("user", json_);

    if (r.status_code != 201) {
        throw std::runtime_error("");
    }

    bot_.getApi().sendMessage(message->chat->id, "Успешная регистрация");
    finished_ = true;
}

void RegisterHandler::getSurname(const TgBot::Message::Ptr& message) {
    json_["surname"] = message->text;
    bot_.getApi().sendMessage(message->chat->id, "Введите имя (на кириллице)");
    nextCommand_ = [this](const TgBot::Message::Ptr& message) {
        getName(message);
    };
}
