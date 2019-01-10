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
#include <fstream>
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
    ~ConnectionInputHandler();

    ConnectionInputHandler();

    void handleNewInput(int fd, std::string);

    void handleEvent(int fd, std::string);

    constexpr unsigned int str2int(const char* str, int h);

    void handleNewUser(rapidjson::Value &, int);

    void handleNewRoom(rapidjson::Value &data, int fd);

    void handleChatMessage(rapidjson::Value &value, int fd);

    void handleCanvasSync(rapidjson::Document &, int fd);

    void sendCurrentRoomsData(int fd);

    size_t intValue(const std::string &value);

    void setServer(Server *server);

    void handleNewGame(rapidjson::Value &d, int fd);

    void handleVictory(std::string roomName, int fd);

    void handleJoinRoom(rapidjson::Value &value, int fd);

    void handleUserQuit(int fd);
};

#include "Server.h"
#define NEW_ROOM "NEW_ROOM"
#define CHAT_MSG "CHAT_MSG"
#define GET_ROOM_LIST "GET_ROOM_LIST"
#define REQUEST "REQUEST"
#define NEW_USER "NEW_USER"
#define NEW_GAME "NEW_GAME"
#define SYN_CANVAS "CANVAS"
#define JOIN_ROOM "JOIN_ROOM"

#endif //KALAMBURY_SERVER_CONNECTIONINPUTHANDLER_H
