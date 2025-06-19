#pragma once

#include "command_handler.h"
#include "register_handler.h"

#include <unordered_map>
#include <cstdint>
#include <functional>
#include <tgbot/tgbot.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Bot : public TgBot::Bot {
public:
    Bot();

private:
    std::unordered_map<int64_t, CommandHandler> stateMap_;
};
