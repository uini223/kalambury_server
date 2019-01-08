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
