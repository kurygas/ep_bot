#pragma once

#include "command_handler.h"

class CreateSemesterHandler : public CommandHandler {
public:
    using CommandHandler::CommandHandler;

private:
    void start(const TgBot::Message::Ptr& message) override;
    void getSemesterNumber(const TgBot::Message::Ptr& message);
    void getSubject(const TgBot::CallbackQuery::Ptr& callbackQuery);
    void getStart(const TgBot::Message::Ptr& message);
    void getEnd(const TgBot::Message::Ptr& message);
    void getGroupId(const TgBot::CallbackQuery::Ptr& callbackQuery);
};
