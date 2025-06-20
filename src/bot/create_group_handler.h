#pragma once

#include "command_handler.h"

class CreateGroupHandler : public CommandHandler {
public:
    explicit CreateGroupHandler(Bot& bot, const TgBot::Message::Ptr& message);

private:
    void getName(const TgBot::Message::Ptr& message);
};
