//
// Created by ramon on 05.01.19.
//

#ifndef KALAMBURY_SERVER_DATASTORAGE_H
#define KALAMBURY_SERVER_DATASTORAGE_H

#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include "User.h"
#include "RoomData.h"

class DataStorage {
    std::unordered_map<int, User> users;
    std::unordered_map<std::string, RoomData> rooms;
    std::vector<int> emptyVector;
    std::vector<std::string> passwords;

public:
    DataStorage();

    void addUser(User);

    void removeUser(int);

    void addRoom(RoomData roomData);

    std::unordered_map<std::string, RoomData> *getRooms();

    std::string toString();

    bool doesRoomAlreadyExists(std::string roomName);

    std::vector<int> &getRoomGuests(std::string roomName);

    void startNewGameForRoom(std::string roomName, int ownerId);

    std::string rollNewPassword();

    bool isThatPassword(std::string roomName, std::string text);

    bool addGuestToRoom(std::string &roomName, int);

    std::string getUserName(int fd);

    void removeRoom(std::string roomName);

    int getRoomOwnerId(std::string&);

    RoomData &getRoom(std::string roomName);

    void clearData();
};


#endif //KALAMBURY_SERVER_DATASTORAGE_H
