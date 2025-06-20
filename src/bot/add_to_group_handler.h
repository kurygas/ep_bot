#pragma once

#include "command_handler.h"

class AddToGroupHandler : public CommandHandler {
public:
    explicit AddToGroupHandler(Bot& bot, const TgBot::Message::Ptr& message);

private:
    void getGroupName(const TgBot::Message::Ptr& message);
    void getUserList(const TgBot::Message::Ptr& message);
};
