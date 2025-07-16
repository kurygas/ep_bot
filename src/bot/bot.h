#pragma once

#include "command_handler.h"
#include "register_handler.h"

#include <unordered_map>
#include <cstdint>
#include <memory>
#include <functional>
#include <tgbot/tgbot.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Bot : public TgBot::Bot {
public:
    Bot();

private:
    template<typename T>
    void process(const T& data) {
        if (commandMap_.contains(data->from->id)) {
            try {
                commandMap_[data->from->id]->process(data);
            }
            catch (...) {
                commandMap_.erase(data->from->id);

                if constexpr (std::is_same_v<T, TgBot::CallbackQuery::Ptr>) {
                    getApi().sendMessage(data->message->chat->id, "Произошла ошибка");
                }
                else {
                    getApi().sendMessage(data->chat->id, "Произошла ошибка");
                }
                
                return;
            }

            if (commandMap_.contains(data->from->id) && commandMap_[data->from->id]->isFinished()) {
                commandMap_.erase(data->from->id);
            }
        }
    }

    template<typename T>
    void createHandler(const TgBot::Message::Ptr& message) {
        commandMap_[message->from->id] = std::make_unique<T>(*this);
    }

    std::unordered_map<int64_t, std::unique_ptr<CommandHandler>> commandMap_;
};
