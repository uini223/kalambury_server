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

class RoomData: public AbstractData {
    std::string name;
    int ownerId;
    std::vector<int> guests;
    std::string currentPassowrd;
public:
    RoomData() {}
    RoomData(std::string name, int ownerId) : name(std::move(name)), ownerId(ownerId) {};

    void changeOwner(int);

    void changePassword(std::string);

    bool addGuest(int fd);

    bool isPassowrdCorrect(std::string);

    std::vector<int>& getGuests();

    std::string toString() override;

    std::string getName() {
        return name;
    }
};
#endif //KALAMBURY_SERVER_ROOMDATA_H
