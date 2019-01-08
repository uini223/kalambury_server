//
// Created by Emil on 1/8/19.
//

#include "ChatMessage.h"

std::string ChatMessage::toString() {
    return R"({"text": ")" + this->text + "\"}";
}

ChatMessage::ChatMessage(const std::string &text) : text(text) {}
