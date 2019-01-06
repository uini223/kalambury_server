//
// Created by ramon on 05.01.19.
//

#include "../headers/ConnectionInputHandler.h"
#include "../headers/WebMessageParser.h"

ConnectionInputHandler::ConnectionInputHandler() = default;

int ConnectionInputHandler::handleNewInput(std::string input, int fd) {
    int msg_id = 0;
    msg_id = this->parser.getMessageId(input);
    if (this->fds_with_messages[fd].count(msg_id)) {
        this->fds_with_messages[fd][msg_id] += input;
    } else {
        this->fds_with_messages[fd][msg_id] = input;
    }
    if (input.find("STOP") != std::string::npos) { // handle whole message
        std::string data = fds_with_messages[fd][msg_id];
        fds_with_messages[fd][msg_id] = this->parser.parse(data);
//        std::cout<<parser.parse(data)<<std::endl; // for test only
        return msg_id;
    }
    return -1;
}

std::string ConnectionInputHandler::getMsgByMsgID(int msg_id, int fd){
//    MSGS_WITH_FDS::iterator it = this->fds_with_messages.find(fd);
//    if(it != this->fds_with_messages.end()){
//        MSGS_WITH_IDS &innerMap = it->second;
//        MSGS_WITH_IDS::iterator innerIt = innerMap.find(msg_id);
//        if(innerIt != innerMap.end()){
//            return innerIt->second;
//        }
//    }
    std::string message = this->fds_with_messages[fd][msg_id];
    this->fds_with_messages[fd][msg_id].erase();
    return message;
}

void ConnectionInputHandler::handleEvent(int fd, int msg_id, Server* server) {
    rapidjson::Document d;
    std::string message = getMsgByMsgID(msg_id, fd);
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
    auto message = this->parser.createMessage("ANSWER", "NEW-ROOM", data);
    server -> sendMessageToAll(parser.packString(message));
}
