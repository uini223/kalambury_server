//
// Created by Emil on 1/8/19.
//

#include "ChatMessage.h"

std::string ChatMessage::toString() {
    return R"({"text": ")" + this->text +
            R"(","roomName": )" + "\"" + this->roomName + "\"}";
}

ChatMessage::ChatMessage(const std::string &text, std::string chatName) {
    this->text = text;
    this->roomName = chatName;
}


