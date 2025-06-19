#include "command_handler.h"
#include "bot.h"
#include "api.h"

CommandHandler::CommandHandler(Bot& bot)
: bot_(bot) {}

void CommandHandler::processMessage(const TgBot::Message::Ptr& message) {
    nextCommand_(message);
}

void CommandHandler::checkRegistration(const TgBot::Message::Ptr& message) {
    if (!Api::userExist(message->from->id)) {
        bot_.getApi().sendMessage(message->chat->id, "Вы не зарегестрированы");
        throw std::runtime_error("");
    }
}

void CommandHandler::checkTeacher(const TgBot::Message::Ptr& message) {
    
}
