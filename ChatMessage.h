//
// Created by Emil on 1/8/19.
//

#ifndef KALAMBURY_SERVER_CHATMESSAGE_H
#define KALAMBURY_SERVER_CHATMESSAGE_H


#include "headers/AbstractData.h"

class ChatMessage: public AbstractData {
    std::string text;
    std::string roomName;
public:
    explicit ChatMessage(const std::string &text, std::string chatName);

    std::string toString() override;
};


#endif //KALAMBURY_SERVER_CHATMESSAGE_H
