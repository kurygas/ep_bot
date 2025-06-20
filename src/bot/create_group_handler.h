#pragma once

#include "command_handler.h"

class CreateGroupHandler : public CommandHandler {
public:
    using CommandHandler::CommandHandler;

private:
    void start(const TgBot::Message::Ptr& message) override;
    void getName(const TgBot::Message::Ptr& message);
};
