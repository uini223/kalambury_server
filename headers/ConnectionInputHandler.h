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

typedef std::map<int, std::string> MSGS_WITH_IDS;
typedef std::map<int, std::map<int, std::string>> MSGS_WITH_FDS;

class ConnectionInputHandler {
    std::map<int, std::map<int, std::string>> fds_with_messages;
    DataStorage dataStorage;
    WebMessageParser parser;

public:
    ConnectionInputHandler();
    int handleNewInput(std::string input, int fd);
    std::string getMsgByMsgID(int msg_id, int fd);
    void handleEvent(int fd, int msg_id, Server* server);
    constexpr unsigned int str2int(const char* str, int h);
    void handleNewUser(rapidjson::Value &, int);

    void handleNewRoom(rapidjson::Value &data, int fd, Server *server);
};

#include "Server.h"

#endif //KALAMBURY_SERVER_CONNECTIONINPUTHANDLER_H
