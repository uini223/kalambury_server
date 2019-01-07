//
// Created by Emil on 1/6/19.
//

#include "../headers/RoomData.h"

std::string RoomData::toString() {
    std::string guests = "";
    int i = 0;
    for(int guest: this->guests) {
        if (i != 0) {
           guests += ",";
        }
        i++;
    }
    return "{\"name\": " + this->name + "," +
        "\"ownerId\": " + std::to_string(this->ownerId) + "," +
        "\"guests\": " + guests + "}";

}
