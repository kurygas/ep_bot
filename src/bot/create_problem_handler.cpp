#include "create_problem_handler.h"
#include "bot.h"
#include "api.h"

void CreateProblemHandler::start(const TgBot::Message::Ptr& message) {
    const auto keyboard = createKeyboard(
        std::make_pair("АиСД", "0"), 
        std::make_pair("ВВП", "1"), 
        std::make_pair("АКОС", "2")
    );
    bot_.getApi().sendMessage(message->chat->id, "Выберите предмет", nullptr, nullptr, keyboard);
    nextCommand_ = [this](const TgBot::CallbackQuery::Ptr& callbackQuery) {
        getSubject(callbackQuery);
    };
}

void CreateProblemHandler::getSubject(const TgBot::CallbackQuery::Ptr& callbackQuery) {
    bot_.getApi().sendMessage(callbackQuery->message->chat->id, (callbackQuery->data == "0" ? "Вы выбрали аисд" : "Вы выбрали что-то другое"));
    nextCommand_ = std::monostate();
}
