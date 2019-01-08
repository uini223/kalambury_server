#include <utility>

#include <utility>

#include <utility>

#include <utility>

#include <utility>

#include <utility>

#include <utility>

#include <utility>

//
// Created by Emil on 12/30/18.
//
#include "../headers/WebMessageParser.h"
#include <iostream>
#include "../libs/rapidjson/document.h"
#include "../libs/rapidjson/stringbuffer.h"
#include "../libs/rapidjson/writer.h"

// TODO this might return packageStructure to discuse
std::string WebMessageParser::parse(std::string data) {
    PackageStucture packageStucture;
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
    return this->createMessageHeader( INFO,  ERROR) + this->createMessageContent(std::move(errorMessage));
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
    if (content.find('{') == std::string::npos || content.find('[') == std::string::npos) {
        content = "\"" + content + "\"";
    }
    return "\"content\": " + content + "}" + STOP;
}
