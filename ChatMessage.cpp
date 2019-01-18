#include <utility>

//
// Created by Emil on 1/8/19.
//

#include "ChatMessage.h"

std::string ChatMessage::toString() {
    return R"({"text": ")" + this->text +
            R"(","roomName": )" + "\"" + this->roomName + "\","  +
            R"("sender": ")" + this->sender + "\"}";
}

ChatMessage::ChatMessage(const std::string &text, std::string chatName, std::string sender) : sender(std::move(sender)) {
    this->text = text;
    this->roomName = chatName;
}


