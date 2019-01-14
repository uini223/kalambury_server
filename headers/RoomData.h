#include <utility>

//
// Created by Emil on 1/6/19.
//

#ifndef KALAMBURY_SERVER_ROOMDATA_H
#define KALAMBURY_SERVER_ROOMDATA_H

#include <string>
#include <vector>
#include <algorithm>
#include "AbstractData.h"
#include "User.h"

class RoomData: public AbstractData {
    std::string name;
    std::string owner;
    int ownerId;
    std::vector<int> guests;
    std::string currentPassword;
public:
    RoomData() {}
    RoomData(std::string name, std::string owner, int ownerId, std::string currentPassword)
            : name(std::move(name)), owner(owner), ownerId(ownerId), currentPassword(currentPassword) {};

    void changeOwner(User&);

    void changePassword(std::string);

    bool addGuest(int fd);

    bool isPassowrdCorrect(std::string);

    void oldOwnerLeft();

    void setOwner(const std::string &owner);

    void removeGuest(int fd);

    std::string getOwnerName();

    void setOwnerId(int);

    int getOwnerId();

    std::vector<int>& getGuests();

    std::string toString() override;

    std::string getName() {
        return name;
    }
};
#endif //KALAMBURY_SERVER_ROOMDATA_H
