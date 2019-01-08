#include <utility>

//
// Created by Emil on 1/6/19.
//

#ifndef KALAMBURY_SERVER_ROOMDATA_H
#define KALAMBURY_SERVER_ROOMDATA_H

#include <string>
#include <unordered_set>
#include "AbstractData.h"

class RoomData: public AbstractData {
    std::string name;
    int ownerId;
    std::unordered_set<int> guests;
public:
    RoomData() {}
    RoomData(std::string name, int ownerId) : name(std::move(name)), ownerId(ownerId) {};

    std::string toString() override;

    std::string getName() {
        return name;
    }
};
#endif //KALAMBURY_SERVER_ROOMDATA_H
