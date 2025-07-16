#pragma once

#include "command_handler.h"

class CreateProblemHandler : public CommandHandler {
public:
    using CommandHandler::CommandHandler;

private:
    void start(const TgBot::Message::Ptr& message) override;
    void getName(const TgBot::Message::Ptr& message);
    void getStatement(const TgBot::Message::Ptr& message);
    void getSubject(const TgBot::CallbackQuery::Ptr& callbackQuery);
    void getSemesterNumber(const TgBot::Message::Ptr& message);
};
