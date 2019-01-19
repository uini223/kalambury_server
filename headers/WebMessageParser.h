//
// Created by Emil on 12/30/18.
//

#ifndef KALAMBURY_SERVER_WEBMESSAGEPARSER_H
#define KALAMBURY_SERVER_WEBMESSAGEPARSER_H

#define START_LENGTH 5
#define STOP_LENGTH 4
#define START "START"
#define STOP "STOP"
#define INFO "INFO"
#define ERROR "ERROR"
#define ANSWER "ANSWER"
#define OK "OK"

#include <string>
#include <vector>
#include <random>
#include "../libs/rapidjson/pointer.h"
#include "AbstractData.h"

class WebMessageParser {
    std::default_random_engine engine;
    std::uniform_int_distribution<int> dist;
public:
    WebMessageParser();

    std::string parse(std::string data);

    std::string createMessage(std::string eventType, std::string eventName, std::string content);

    std::string createErrorMessage(std::string errorMessage);

    std::string createInfoMessage(std::string name, AbstractData &content);

    std::string createAnswerMessage(std::string name, AbstractData &content);

    std::string createAnswerMessage(std::string name, std::string &);

    std::string createVictoryMessage(std::string &roomName, std::string fd);

    std::string createOKMessage();

    std::string createRoomDeletedMessage(std::string data);

private:
    std::string createMessageHeader(std::string eventType, std::string eventName);

    std::string createMessageContent(std::string content);

    void eraseStart(std::string &data);

    void eraseStop(std::string &data);
};

#endif  //KALAMBURY_SERVER_WEBMESSAGEPARSER_H
