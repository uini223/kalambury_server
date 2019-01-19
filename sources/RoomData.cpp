#include <utility>

//
// Created by Emil on 1/6/19.
//

#include "../headers/RoomData.h"

std::string RoomData::toString() {
    return R"({"name": ")" + this->name + "\"," +
            R"("ownerName": ")" + this->owner + "\"," +
            R"("guests": ")" + std::to_string(this->guests.size()) + "\"," +
            R"("currentPassword": ")" + this->currentPassword + "\"}";

}

void RoomData::changePassword(std::string newPassword) {
    this->currentPassword = std::move(newPassword);
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
void RoomData::changeOwner(User &user) {
    int oldOwnerId = this->ownerId;
    this->ownerId = user.getId();
    this->owner = user.getName();
    this->guests.push_back(oldOwnerId);
    this->removeGuest(user.getId());
}

//checks if given text (message on chat) is correct
bool RoomData::isPassowrdCorrect(std::string text) {
//    std::transform(text.begin(), text.end(), text.begin(), ::tolower);
//    std::transform(this->currentPassword.begin(), this->currentPassword.end(), this->currentPassword.begin(),
//            ::tolower);
    return this->currentPassword == text;
}

std::string RoomData::getOwnerName() {
    return this->owner;
}

void RoomData::setOwner(const std::string &owner) {
    this->owner = owner;
}

void RoomData::removeGuest(int fd) {
    for(unsigned int i=0; i<this->guests.size(); i++) {
        if(this->guests[i] == fd) {
            this->guests.erase(this->guests.begin() + i);
            break;
        }
    }
}

int RoomData::getOwnerId() {
    return ownerId;
}

void RoomData::setOwnerId(int id) {
    this->ownerId = id;
}
