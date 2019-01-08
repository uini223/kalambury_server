//
// Created by ramon on 05.01.19.
//

#ifndef KALAMBURY_SERVER_CONNECTIONINPUTHANDLER_H
#define KALAMBURY_SERVER_CONNECTIONINPUTHANDLER_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <map>
#include "DataStorage.h"
#include "../libs/rapidjson/document.h"
#include "../libs/rapidjson/writer.h"
#include "../libs/rapidjson/stringbuffer.h"
#include "WebMessageParser.h"

class Server;


class ConnectionInputHandler {
    std::map<int, std::string> fds_with_messages;
    DataStorage dataStorage;
    WebMessageParser parser;
    Server *server;

public:
    ConnectionInputHandler();

    explicit ConnectionInputHandler(Server *server);

    void handleNewInput(int fd, std::string);

    void handleEvent(int fd, std::string);

    constexpr unsigned int str2int(const char* str, int h);
    void handleNewUser(rapidjson::Value &, int);

    void handleNewRoom(rapidjson::Value &data, int fd);

    void handleChatMessage(rapidjson::Value &value, int fd);

    void sendCurrentRoomsData(int fd);

    size_t intValue(const std::string &value);
};

#include "Server.h"

#endif //KALAMBURY_SERVER_CONNECTIONINPUTHANDLER_H
