#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <variant>
#include <tgbot/tgbot.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Bot;

class CommandHandler {
public:
    using MessageHandler = std::function<void(const TgBot::Message::Ptr&)>;
    using CallbackQueryHandler = std::function<void(const TgBot::CallbackQuery::Ptr&)>;

    explicit CommandHandler(Bot& bot);

    template<typename T>
    void process(const T& data) {
        std::get<std::function<void(const T&)>>(nextCommand_)(data);
    }

    bool isFinished() const;

    static std::vector<std::string> split(const std::string& str);

    virtual ~CommandHandler() = default;

protected:
    virtual void start(const TgBot::Message::Ptr& message) = 0;
    void checkRegistration(const TgBot::Message::Ptr& message);
    void checkTeacher(const TgBot::Message::Ptr& message);

    template<typename... T>
    static TgBot::InlineKeyboardMarkup::Ptr createKeyboard(const std::pair<std::string, std::string>& data, const T&... args) {
        const auto keyboard = createKeyboard(args...);
        const auto button = std::make_shared<TgBot::InlineKeyboardButton>();
        button->text = data.first;
        button->callbackData = data.second;
        keyboard->inlineKeyboard.push_back({button});
        return keyboard;
    }

    Bot& bot_;
    json json_;
    std::variant<std::monostate, MessageHandler, CallbackQueryHandler> nextCommand_;
};

template<>
inline TgBot::InlineKeyboardMarkup::Ptr CommandHandler::createKeyboard(const std::pair<std::string, std::string>& data) {
        const auto keyboard = std::make_shared<TgBot::InlineKeyboardMarkup>();
        const auto button = std::make_shared<TgBot::InlineKeyboardButton>();
        button->text = data.first;
        button->callbackData = data.second;
        keyboard->inlineKeyboard.push_back({button});
        return keyboard;
}
