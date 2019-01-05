//
// Created by ramon on 05.01.19.
//

#include "ConnectionInputHandler.h"
#include "WebMessageParser.h"

ConnectionInputHandler::ConnectionInputHandler() = default;

void ConnectionInputHandler::handleNewInput(std::string input, int fd) {
    WebMessageParser parser;
    int msg_id = 0;
    int pckg_id = 0;
    if (input.find("START") != std::string::npos && input.find("STOP") != std::string::npos) {
        msg_id = parser.getMessageId(input);
        pckg_id = parser.getPackageNumber(input);
        input = input.substr(1, input.size() - 1);
        if (std::find(this->fds.begin(), this->fds.end(), fd) != this->fds.end()) {
            this->fds.push_back(fd);
            this->messages.push_back(input);
            this->msg_ids.push_back(msg_id);
        } else {
            if (std::find(this->msg_ids.begin(), this->msg_ids.end(), msg_id) != this->msg_ids.end()) {
                this->fds.push_back(fd);
                this->messages.push_back(input);
                this->msg_ids.push_back(msg_id);
            } else {
                for (int i = 0; i < this->fds.size(); i++) {
                    if (this->fds[i] == fd && this->msg_ids[i] == msg_id) {
                        this->messages[i] += input;
                    }
                }
            }
        }
        //TODO użycie rapidjson i rozpakowanie wiadomości (zamiana w obiekt) + wywołanie odpowiedniej funkcji
        //znane jest fd autora wiadomości, id wiadomości i jej treść
        //z zawartości można wyciąŋnąć nazwę i typ
    } else if (input.find("STOP") == std::string::npos) {
        for (int i = 0; i < this->fds.size(); i++) {
            if (this->fds[i] == fd && this->msg_ids[i] == msg_id) {
                std::cout << this->messages[i];
            }
        }
    }
}
