//
// Created by Emil on 12/30/18.
//

#ifndef KALAMBURY_SERVER_WEBMESSAGEPARSER_H
#define KALAMBURY_SERVER_WEBMESSAGEPARSER_H

#define START "START"
#define START_LENGTH 5
#define ID_LENGTH 3
#define PACKAGE_DATA_SIZE 250
#define STOP "STOP"
#define STOP_LENGTH 4

#include <string>
#include <vector>
#include <random>
#include "PackageStucture.h"
#include "../libs/rapidjson/pointer.h"
#include "AbstractData.h"

class WebMessageParser {
    std::default_random_engine engine;
    std::uniform_int_distribution<int> dist;
public:
    WebMessageParser();

    std::string parse(std::string data);

    int getMessageId(std::string &data);

    std::string createMessage(std::string eventType, std::string eventName, AbstractData &data);

private:
    std::string toString(int);

    void eraseStart(std::string &data);

    void eraseStop(std::string &data);

    int getRandomId();
};

#endif  //KALAMBURY_SERVER_WEBMESSAGEPARSER_H
