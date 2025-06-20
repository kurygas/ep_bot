#include "bot.h"
#include "config.h"
#include "register_handler.h"
#include "create_group_handler.h"
#include "add_to_group_handler.h"
#include "create_problem_handler.h"

Bot::Bot()
: TgBot::Bot(Config::botToken) {
    getEvents().onCommand("register", [this](const TgBot::Message::Ptr& message) {
        createHandler<RegisterHandler>(message);
        process(message);
    });

    getEvents().onCommand("create_group", [this](const TgBot::Message::Ptr& message) {
        createHandler<CreateGroupHandler>(message);
        process(message);
    });

    getEvents().onCommand("add_to_group", [this](const TgBot::Message::Ptr& message) {
        createHandler<AddToGroupHandler>(message);
        process(message);
    });

    getEvents().onCommand("create_problem", [this](const TgBot::Message::Ptr& message) {
        createHandler<CreateProblemHandler>(message);
        process(message);
    });

    getEvents().onAnyMessage([this](const TgBot::Message::Ptr& message) {
        process(message);
    });

    getEvents().onCallbackQuery([this](const TgBot::CallbackQuery::Ptr& callbackQuery) {
        process(callbackQuery);
        getApi().answerCallbackQuery(callbackQuery->id);
    });

    TgBot::TgLongPoll longPoll(*this);

    while (true) {
        longPoll.start();
    }
}
