#pragma once

#include "command_handler.h"

class RegisterHandler : public CommandHandler {
public:
    explicit RegisterHandler(Bot& bot, const TgBot::Message::Ptr& message);

private:
    void getName(const TgBot::Message::Ptr& message);
    void getSurname(const TgBot::Message::Ptr& message);
};
