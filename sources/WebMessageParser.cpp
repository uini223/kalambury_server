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

std::string WebMessageParser::createMessage(std::string eventType, std::string eventName, AbstractData &data) {
    return "START{\"type\": " + eventType + "," +
           "\"name\": " + eventName  + "," +
           "\"content\": " + data.toString() + "}" + "STOP";
}

WebMessageParser::WebMessageParser() {
    std::uniform_int_distribution<int> dist(1, 999);
    this-> dist = dist;
}
