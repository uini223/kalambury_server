#include <utility>

#include <utility>

#include <utility>

#include <utility>

//
// Created by ramon on 05.01.19.
//

#include "../headers/DataStorage.h"

DataStorage::DataStorage() = default;

void DataStorage::addUser(User user) {
    this->users[user.getId()] = user;
}

void DataStorage::addRoom(RoomData data) {
    this->rooms[data.getName()] = data;
}

std::unordered_map<std::string, RoomData> &DataStorage::getRooms() {
    return this->rooms;
}

// sprawdza czy pokoj istnieje
bool DataStorage::doesRoomAlreadyExists(std::string roomName) {
    printf(this->rooms.find(roomName) != this->rooms.end()? "true\n": "false\n");
    return this->rooms.find(roomName) != this->rooms.end();
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

// returns all room guests (zgadujących) when there is no room
// empty vector is returned
std::vector<int> &DataStorage::getRoomGuests(std::string roomName) {
    if(this->doesRoomAlreadyExists(roomName)) {
        return this->rooms[roomName].getGuests();
    }
    return this->emptyVector;
}

// initiate new game for room
// changes the owner (master) and rools new passowrd
// if room doesn't exist do nothing
void DataStorage::startNewGameForRoom(std::string roomName, int ownerId) {
    if(this->doesRoomAlreadyExists(roomName)) {
        this->rooms[roomName].changeOwner(this->users[ownerId]);
        this->rooms[roomName].changePassword(this->rollNewPassword());
    }
}

// TODO read names from file and rool one, we don't want to hardcoded passwords xD
// maybe this need old password as parameter so it don't choose same password again
std::string DataStorage::rollNewPassword() {
    return "Komputer";
}

// checks if given text (message on chat) is correct
// if room with given name doesn't exist return false
bool DataStorage::isThatPassword(std::string roomName, std::string text) {
    if(this->doesRoomAlreadyExists(roomName)) {
        return this->rooms[roomName].isPassowrdCorrect(std::move(text));
    } else {
        return false;
    }
}

bool DataStorage::addGuestToRoom(std::string &roomName, int fd) {
    if(this->doesRoomAlreadyExists(roomName)) {
        return this->rooms[roomName].addGuest(fd);
    } else {
        return false;
    }
}

std::string DataStorage::getUserName(int fd) {
    if(this->users.find(fd) != this->users.end()) {
        return this->users[fd].getName();
    }
    return "";
}

void DataStorage::removeUser(int fd) {
    if(this->users.find(fd) != this->users.end()) {
        this->users.erase(fd);
    }
}
