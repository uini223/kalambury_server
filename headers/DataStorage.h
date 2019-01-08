//
// Created by ramon on 05.01.19.
//

#ifndef KALAMBURY_SERVER_DATASTORAGE_H
#define KALAMBURY_SERVER_DATASTORAGE_H

#include <vector>
#include <string>
#include <unordered_map>
#include "User.h"
#include "RoomData.h"

class DataStorage {
    std::vector<User> users;
    std::unordered_map<std::string, RoomData> rooms;
public:
    DataStorage();
    void addUser(User);
    void addRoom(RoomData roomData);
    std::unordered_map<std::string, RoomData>& getRooms();
    std::string toString();
    bool doesRoomAlreadyExists(std::string roomName);
};


#endif //KALAMBURY_SERVER_DATASTORAGE_H
