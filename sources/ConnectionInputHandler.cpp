//
// Created by ramon on 05.01.19.
//

#include "../headers/ConnectionInputHandler.h"
#include "../headers/WebMessageParser.h"
#include "../ChatMessage.h"

void ConnectionInputHandler::handleNewInput(int fd, std::string input) {
    if (this->fds_with_messages.count(fd)) {
        this->fds_with_messages[fd] += input;
    } else {
        this->fds_with_messages[fd] = input;
    }
    while (this->fds_with_messages[fd].find("STOP") != std::string::npos) { // handle whole message
        std::string data = this->fds_with_messages[fd];
        int stopIdx = data.find("STOP");
        data = data.substr(0, stopIdx+4);
        this->fds_with_messages[fd].erase(0, stopIdx+4);
        this->handleEvent(fd, this->parser.parse(data));
    }
}

void ConnectionInputHandler::handleEvent(int fd, std::string message) {
    rapidjson::Document d;
    d.Parse(message.c_str());
    rapidjson::Value& name = d["name"];
    rapidjson::Value& type = d["type"];
    rapidjson::Value& content = d["content"];

    auto event_name = std::string(name.GetString());
    auto event_type = std::string(type.GetString());

    if(event_type == "ANSWER"){
    } else if(intValue(event_type) == intValue("REQUEST")) {
        if (intValue(event_name) == intValue("NEW-USER")) {
            this->handleNewUser(content,fd);
        }
        if (intValue(event_name) == intValue("NEW-ROOM")) {
            this->handleNewRoom(content, fd);
        }
        if (intValue(event_name) == intValue("GET-ROOM-LIST")) {
            this->sendCurrentRoomsData(fd);
        }
        if (intValue(event_name) == intValue("SYN_CANVAS")) {
            this->handleCanvasSync(d, fd);
        }
    } else if(event_type == "INFO") {
        if( event_name == "CHAT-MSG") this->handleChatMessage(content, fd);
    }
}

constexpr unsigned int ConnectionInputHandler::str2int(const char* str, int h){
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

void ConnectionInputHandler::handleNewUser(rapidjson::Value &name, int id) {
    User user(id, name["name"].GetString());
    this->dataStorage.addUser(user);
}

void ConnectionInputHandler::handleNewRoom(rapidjson::Value &data, int fd) {
    if (data["name"].IsString()) {
        std::string name = data["name"].GetString();
        if (this->dataStorage.doesRoomAlreadyExists(name)) {
            server->sendMessage(fd, this->parser.createErrorMessage("Room with given name already exits"));
        } else {
            RoomData roomData(name, fd);
            this->dataStorage.addRoom(roomData);
            server->sendMessageToAllExceptOne(this->parser.createAnswerMessage(NEW_ROOM, roomData), fd);
        }
    }
}

void ConnectionInputHandler::handleChatMessage(rapidjson::Value &data, int fd) {
    std::string text = data["text"].GetString();
    ChatMessage message(text);
    // TODO check if is correct answer
    server->sendMessageToAllExceptOne(this->parser.createInfoMessage(CHAT_MSG, message), fd);
}

void ConnectionInputHandler::handleCanvasSync(rapidjson::Document &d, int fd) {
    d["type"].SetString(ANSWER);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);
    server->sendMessageToAllExceptOne(buffer.GetString(), fd);
}

void ConnectionInputHandler::sendCurrentRoomsData(int fd) {
    std::string all = "[";
    int i = 0;
    for (const auto &entry: this->dataStorage.getRooms()) {
        if(i != 0) {
            all += ',';
        }
        RoomData roomData = entry.second;
        all += roomData.toString();
        i++;
    }
    all += "]";
    server->sendMessage(fd, this->parser.createAnswerMessage(GET_ROOM_LIST, all));

}

size_t ConnectionInputHandler::intValue(const std::string &value) {
    return std::hash<std::string>{}(value);
}

ConnectionInputHandler::ConnectionInputHandler() = default;

ConnectionInputHandler::~ConnectionInputHandler() = default;

void ConnectionInputHandler::setServer(Server *server) {
    this->server = server;
}
