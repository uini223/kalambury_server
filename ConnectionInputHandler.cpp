//
// Created by ramon on 05.01.19.
//

#include "ConnectionInputHandler.h"
#include "WebMessageParser.h"

ConnectionInputHandler::ConnectionInputHandler() = default;

void ConnectionInputHandler::handleNewInput(std::string input, int fd) {
    WebMessageParser parser;
    int msg_id = 0;
    msg_id = parser.getMessageId(input);
    if (this->fds_with_messages[fd].count(msg_id)) {
        this->fds_with_messages[fd][msg_id] += input;
    } else {
        this->fds_with_messages[fd][msg_id] = input;
    }
    if (input.find("STOP") != std::string::npos) { // handle whole message
        std::string data = fds_with_messages[fd][msg_id];
        fds_with_messages[fd][msg_id] = parser.parse(data);
        std::cout<<data<<std::endl; // for test only
        //TODO return message_id;
    }
    // TODO return -1 // nie ma konca wiadomosci
}
