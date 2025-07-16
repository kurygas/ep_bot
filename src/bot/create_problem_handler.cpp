#include "create_problem_handler.h"
#include "bot.h"
#include "api.h"

void CreateProblemHandler::start(const TgBot::Message::Ptr& message) {
    checkTeacher(message);
    bot_.getApi().sendMessage(message->chat->id, "Введите название задачи");
    nextCommand_ = [this](const TgBot::Message::Ptr& message) {
        getName(message);
    };
}

void CreateProblemHandler::getName(const TgBot::Message::Ptr& message) {
    json_["name"] = message->text;
    bot_.getApi().sendMessage(message->chat->id, "Введите условие задачи");
    nextCommand_ = [this](const TgBot::Message::Ptr& message) {
        getStatement(message);
    };
}

void CreateProblemHandler::getStatement(const TgBot::Message::Ptr& message) {
    json_["statement"] = message->text;
    bot_.getApi().sendMessage(message->chat->id, "Выберите предмет", nullptr, nullptr, createSubjectKeyboard());
    nextCommand_ = [this](const TgBot::CallbackQuery::Ptr& callbackQuery) {
        getSubject(callbackQuery);
    };
}

void CreateProblemHandler::getSubject(const TgBot::CallbackQuery::Ptr& callbackQuery) {
    json_["subject"] = std::stoi(callbackQuery->data);
    bot_.getApi().sendMessage(callbackQuery->message->chat->id, "Введите номер семестра, на который оринетирована задача");
    nextCommand_ = [this](const TgBot::Message::Ptr& message) {
        getSemesterNumber(message);
    };
}

void CreateProblemHandler::getSemesterNumber(const TgBot::Message::Ptr& message) {
    json_["semester_number"] = std::stoi(message->text);
    const auto r = Api::post("problem", json_);

    if (r.status_code != 201) {
        throw std::runtime_error("Ошибка при создании задачи");
    }

    bot_.getApi().sendMessage(message->chat->id, "Задача создана");
    nextCommand_ = std::monostate();
}

