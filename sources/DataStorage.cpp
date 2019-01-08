//
// Created by ramon on 05.01.19.
//

#include "../headers/DataStorage.h"

DataStorage::DataStorage() = default;

void DataStorage::addUser(User user) {
    this->users.push_back(user);
}

void DataStorage::addRoom(RoomData data) {
    this->rooms[data.getName()] = data;
}

std::unordered_map<std::string, RoomData> &DataStorage::getRooms() {
    return this->rooms;
}

bool DataStorage::doesRoomAlreadyExists(std::string roomName) {
    return this->rooms.count(roomName) > 0;
}

std::string DataStorage::toString() {
    std::string final = "{";
    std::string rooms = "[";
    int i = 0;
    for (auto room: this->rooms) {
        if (i != 0) {
            rooms += ",";
        }
        rooms += room.second.toString();
        i++;
    }
    rooms += "]";
    final += "\"rooms\": "+ rooms + "}";
    return final;
}
