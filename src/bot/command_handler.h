#pragma once

#include <cstdint>
#include <functional>
#include <tgbot/tgbot.h>
#include <nlohmann/json.hpp>

class Bot;

class CommandHandler {
public:
    explicit CommandHandler(Bot& bot);

    void processMessage(const TgBot::Message::Ptr& message);

protected:
    void checkRegistration(const TgBot::Message::Ptr& message);
    void checkTeacher(const TgBot::Message::Ptr& message);

    Bot& bot_;
    std::function<void(const TgBot::Message::Ptr&)> nextCommand_;
    json json_;
};
