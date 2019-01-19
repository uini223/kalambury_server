//
// Created by Emil on 12/30/18.
//
#include "../headers/WebMessageParser.h"
#include <iostream>
#include "../libs/rapidjson/document.h"
#include "../libs/rapidjson/stringbuffer.h"
#include "../libs/rapidjson/writer.h"

#define ROOM_DELETED "ROOM_DELETED"

// TODO this might return packageStructure to discuse
std::string WebMessageParser::parse(std::string data) {
    this->eraseStart(data);
    this->eraseStop(data);
    return data;
}

void WebMessageParser::eraseStart(std::string &data) {
    int start = data.find(START);
    if(start != std::string::npos) {
        data.erase(data.find(START), START_LENGTH);
    }
}

void WebMessageParser::eraseStop(std::string &data) {
    int stop = data.find(STOP);
    if(stop != std::string::npos) {
        data.erase(data.find(STOP), STOP_LENGTH);
    }
}

std::string WebMessageParser::createMessage(std::string eventType, std::string eventName, std::string content) {
    return this->createMessageHeader(std::move(eventType), std::move(eventName)) + this->createMessageContent(content);
}

WebMessageParser::WebMessageParser() {
    std::uniform_int_distribution<int> dist(1, 999);
    this-> dist = dist;
}

std::string WebMessageParser::createErrorMessage(std::string errorMessage) {
    return this->createMessageHeader(INFO,  ERROR) + this->createMessageContent(R"({"message": ")" + errorMessage
    + "\"}");
}

std::string WebMessageParser::createMessageHeader(std::string eventType, std::string eventName) {
    return R"(START{"type": ")" + eventType + "\"," +
           R"("name": ")" + eventName  + "\",";
}

std::string WebMessageParser::createInfoMessage(std::string name, AbstractData &data) {
    return createMessage(INFO, std::move(name), data.toString());
}

std::string WebMessageParser::createAnswerMessage(std::string name, AbstractData &data) {
    return createMessage(ANSWER, std::move(name), data.toString());
}

std::string WebMessageParser::createAnswerMessage(std::string name, std::string &data) {
    return createMessage(ANSWER, std::move(name), data);
}

std::string WebMessageParser::createMessageContent(std::string content) {
    if (content.find('[') == -1 && content.find('{')) {
        content = "\"" + content + "\"";
    }

    return "\"content\": " + content + "}" + STOP;
}

std::string WebMessageParser::createVictoryMessage(std::string &roomName, std::string fd) {
    return this->createMessageHeader(INFO, "VICTORY") + R"("roomName": ")" + roomName +
            R"(","winnerId": )" + "\"" + fd + "\"}" + STOP;
}

std::string WebMessageParser::createOKMessage() {
    return this->createMessageHeader(INFO,  OK) + this->createMessageContent("");
}

std::string WebMessageParser::createRoomDeletedMessage(std::string data) {
    std::string message = R"({"roomName": ")" + data + "\"}";
    return this->createMessageHeader(INFO, ROOM_DELETED) + this->createMessageContent(message);
}
