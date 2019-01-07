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
    std::map<int, std::string> ready_for_read;
    DataStorage dataStorage;
    WebMessageParser parser;

public:
    ConnectionInputHandler();
    int handleNewInput(std::string input, int fd);
    std::string getMsgByFd(int fd);
    void handleEvent(int fd, Server* server);
    constexpr unsigned int str2int(const char* str, int h);
    void handleNewUser(rapidjson::Value &, int);

    void handleNewRoom(rapidjson::Value &data, int fd, Server *server);
};

#include "Server.h"

#endif //KALAMBURY_SERVER_CONNECTIONINPUTHANDLER_H
