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

    virtual ~CommandHandler() = default;

    static std::vector<std::string> split(const std::string& str, char splitter = ' ');
    static long long getTime(int day, int month, int year, int h = 0, int min = 0, int sec = 0);

protected:
    virtual void start(const TgBot::Message::Ptr& message) = 0;
    void checkRegistration(const TgBot::Message::Ptr& message);
    void checkTeacher(const TgBot::Message::Ptr& message);

    static TgBot::InlineKeyboardMarkup::Ptr createKeyboard(const std::vector<std::pair<std::string, std::string>>& data);
    static TgBot::InlineKeyboardMarkup::Ptr createSubjectKeyboard();

    Bot& bot_;
    json json_;
    std::variant<std::monostate, MessageHandler, CallbackQueryHandler> nextCommand_;
};
