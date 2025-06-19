#include "bot.h"
#include "config.h"

Bot::Bot()
: TgBot::Bot(Config::botToken) {
    try {
        TgBot::TgLongPoll longPoll(*this);

        while (true) {
            longPoll.start();
        }
    } 
    catch (TgBot::TgException& e) {}
}