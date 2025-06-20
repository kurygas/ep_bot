#pragma once

#include "command_handler.h"

class AddToGroupHandler : public CommandHandler {
public:
    using CommandHandler::CommandHandler;

private:
    void start(const TgBot::Message::Ptr& message) override;
    void getGroupName(const TgBot::Message::Ptr& message);
    void getUserList(const TgBot::Message::Ptr& message);
};
