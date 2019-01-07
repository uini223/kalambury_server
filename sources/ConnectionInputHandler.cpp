//
// Created by ramon on 05.01.19.
//

#include "../headers/ConnectionInputHandler.h"
#include "../headers/WebMessageParser.h"

ConnectionInputHandler::ConnectionInputHandler() = default;

int ConnectionInputHandler::handleNewInput(std::string input, int fd) {
    if (this->fds_with_messages.count(fd)) {
        this->fds_with_messages[fd] += input;
    } else {
        this->fds_with_messages[fd] = input;
    }
    if (this->fds_with_messages[fd].find("STOP") != std::string::npos) { // handle whole message
        std::string data = this->fds_with_messages[fd];
        int stopIdx = data.find("STOP");
        data = data.substr(0, stopIdx);
        this->fds_with_messages[fd].erase(stopIdx, 4);
        this->ready_for_read[fd] = this->parser.parse(data);
        this->fds_with_messages.erase(fd);
        return fd;
    }
    return -1;
}

std::string ConnectionInputHandler::getMsgByFd(int fd){
    return this->ready_for_read[fd];
}

void ConnectionInputHandler::handleEvent(int fd, Server* server) {
    rapidjson::Document d;
    std::string message = getMsgByFd(fd);
    d.Parse(message.c_str());
    rapidjson::Value& name = d["name"];
    rapidjson::Value& type = d["type"];
    rapidjson::Value& content = d["content"];

    auto event_name = std::string(name.GetString());
    auto event_type = std::string(type.GetString());

    if(event_type == "ANSWER"){

    } else if(event_type == "REQUEST") {
        if( event_name == "NEW-USER") this->handleNewUser(content,fd);
        else if( event_name == "NEW-ROOM") this->handleNewRoom(content, fd, server);
    }
}

constexpr unsigned int ConnectionInputHandler::str2int(const char* str, int h){
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

void ConnectionInputHandler::handleNewUser(rapidjson::Value &name, int id) {
    User user(id, name["name"].GetString());
    this->dataStorage.addUser(user);
}

void ConnectionInputHandler::handleNewRoom(rapidjson::Value &data, int fd, Server *server) {
    std::string name = data["name"].GetString();
    RoomData roomData(name, fd);
    this->dataStorage.addRoom(roomData);
    server -> sendMessageToAll(this->parser.createMessage("ANSWER", "NEW-ROOM", roomData));
}
