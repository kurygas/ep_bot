#pragma once

#include "command_handler.h"

class CreateProblemHandler : public CommandHandler {
public:
    using CommandHandler::CommandHandler;

private:
    void start(const TgBot::Message::Ptr& message) override;
    void getSubject(const TgBot::CallbackQuery::Ptr& message);
};
