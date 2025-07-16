#include "command_handler.h"
#include "bot.h"
#include "api.h"

CommandHandler::CommandHandler(Bot& bot)
: bot_(bot) {
    nextCommand_ = [this](const TgBot::Message::Ptr& message) {
        start(message);
    };
}

bool CommandHandler::isFinished() const {
    return std::holds_alternative<std::monostate>(nextCommand_);
}

std::vector<std::string> CommandHandler::split(const std::string& str, const char splitter) {
    std::vector<std::string> result;
    std::string buffer;

    for (const auto& symbol : str) {
        if (symbol == splitter && !buffer.empty()) {
            result.emplace_back(buffer);
            buffer.clear();
        }
        else if (symbol != splitter) {
            buffer.push_back(symbol);
        }
    }

    if (!buffer.empty()) {
        result.emplace_back(buffer);
    }

    return result;
}

long long CommandHandler::getTime(const int day, const int month, const int year, const int h, const int min, const int sec) {
    std::tm timeInfo = {0};
    timeInfo.tm_mday = day;
    timeInfo.tm_mon = month - 1;
    timeInfo.tm_year = year - 1900;
    timeInfo.tm_hour = h;
    timeInfo.tm_min = min;
    timeInfo.tm_sec = sec;
    timeInfo.tm_isdst = 0;
    return std::mktime(&timeInfo);
}

void CommandHandler::checkRegistration(const TgBot::Message::Ptr& message) {
    try {
        Api::findId("user", "tg_id", message->from->id);
    }
    catch (...) {
        bot_.getApi().sendMessage(message->chat->id, "Вы не зарегестрированы");
        throw;
    }
}

void CommandHandler::checkTeacher(const TgBot::Message::Ptr& message) {
    checkRegistration(message);
    const auto user = json::parse(Api::getId("user/", Api::findId("user", "tg_id", message->from->id)).text);

    if (user["user_type"] == 0) {
        bot_.getApi().sendMessage(message->chat->id, "У вас недостаточно прав");
        throw std::runtime_error("");
    }
}

TgBot::InlineKeyboardMarkup::Ptr CommandHandler::createKeyboard(const std::vector<std::pair<std::string, std::string>>& data) {
    const auto keyboard = std::make_shared<TgBot::InlineKeyboardMarkup>();

    for (const auto& [text, callbackData] : data) {
        const auto button = std::make_shared<TgBot::InlineKeyboardButton>();
        button->text = text;
        button->callbackData = callbackData;
        keyboard->inlineKeyboard.push_back({button});
    }

    return keyboard;
}

TgBot::InlineKeyboardMarkup::Ptr CommandHandler::createSubjectKeyboard() {
    return createKeyboard({
        {"АиСД", "0"}, 
        {"ВВП", "1"}, 
        {"АКОС", "2"}
    });
}
