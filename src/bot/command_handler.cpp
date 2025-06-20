#include "command_handler.h"
#include "bot.h"
#include "api.h"

CommandHandler::CommandHandler(Bot& bot)
: bot_(bot) {}

void CommandHandler::processMessage(const TgBot::Message::Ptr& message) {
    nextCommand_(message);
}

bool CommandHandler::isFinished() const {
    return finished_;
}

std::vector<std::string> CommandHandler::split(const std::string& str) {
    std::vector<std::string> result;
    std::string buffer;

    for (const auto& symbol : str) {
        if (symbol == ' ' && !buffer.empty()) {
            result.emplace_back(buffer);
            buffer.clear();
        }
        else if (symbol != ' ') {
            buffer.push_back(symbol);
        }
    }

    if (!buffer.empty()) {
        result.emplace_back(buffer);
    }

    return result;
}

void CommandHandler::checkRegistration(const TgBot::Message::Ptr &message)
{
    try {
        Api::getId("user/", "tg_id", message->from->id);
    }
    catch (...) {
        bot_.getApi().sendMessage(message->chat->id, "Вы не зарегестрированы");
        throw;
    }
}

void CommandHandler::checkTeacher(const TgBot::Message::Ptr& message) {
    checkRegistration(message);
    const auto r = Api::get("user/" + std::to_string(Api::getId("user/", "tg_id", message->from->id)));

    if (json::parse(r.text)["user_type"].get<int>() == 0) {
        bot_.getApi().sendMessage(message->chat->id, "У вас недостаточно прав");
        throw std::runtime_error("");
    }
}
