#include "bot.h"
#include "config.h"
#include "register_handler.h"
#include "create_group_handler.h"
#include "add_to_group_handler.h"

Bot::Bot()
: TgBot::Bot(Config::botToken) {
    getEvents().onCommand("register", [this](const TgBot::Message::Ptr& message) {
        commandMap_[message->from->id] = std::make_unique<RegisterHandler>(*this, message);
    });

    getEvents().onCommand("create_group", [this](const TgBot::Message::Ptr& message) {
        commandMap_[message->from->id] = std::make_unique<CreateGroupHandler>(*this, message);
    });

    getEvents().onCommand("add_to_group", [this](const TgBot::Message::Ptr& message) {
        commandMap_[message->from->id] = std::make_unique<AddToGroupHandler>(*this, message);
    });

    getEvents().onAnyMessage([this](const TgBot::Message::Ptr& message) {
        if (commandMap_.contains(message->from->id)) {
            try {
                commandMap_[message->from->id]->processMessage(message);
            }
            catch (...) {
                getApi().sendMessage(message->chat->id, "Упс! Произошла ошибка");
                commandMap_.erase(message->from->id);
            }

            if (commandMap_.contains(message->from->id) && commandMap_[message->from->id]->isFinished()) {
                commandMap_.erase(message->from->id);
            }
        }
    });

    TgBot::TgLongPoll longPoll(*this);

    while (true) {
        longPoll.start();
    }
}