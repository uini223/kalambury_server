#include <utility>

//
// Created by Emil on 1/6/19.
//

#include "../headers/RoomData.h"

std::string RoomData::toString() {
    std::string guests = "[";
    int i = 0;
    for(int guest: this->guests) {
        if (i != 0) {
           guests += ",";
        }
        guests+= std::to_string(guest);
        i++;
    }
    guests += ']';
    return R"({"name": ")" + this->name + "\"," +
            R"("ownerId": ")" + std::to_string(this->ownerId) + "\"," +
        "\"guests\": " + guests + "}";

}

void RoomData::changePassword(std::string newPassword) {
    this->currentPassowrd = std::move(newPassword);
}

bool RoomData::addGuest(int fd) {
    if(this->guests.size() < 10) {
        this->guests.push_back(fd);
        return true;
    } else {
        return false;
    }
}

std::vector<int>& RoomData::getGuests() {
    return this->guests;
}

//changes owner removes new one from guest and pushes old one to guest
void RoomData::changeOwner(int ownerId) {
    int oldOwner = this->ownerId;
    this->ownerId = ownerId;
    this->guests.push_back(ownerId);
    this->guests.remove(oldOwner);
}

//checks if given text (message on chat) is correct
bool RoomData::isPassowrdCorrect(std::string text) {
    std::transform(text.begin(), text.end(), text.begin(), ::tolower);
    std::transform(this->currentPassowrd.begin(), this->currentPassowrd.end(), this->currentPassowrd.begin(),
            ::tolower);
    return text.find(currentPassowrd) != std::string::npos;
}
