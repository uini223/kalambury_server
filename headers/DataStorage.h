//
// Created by ramon on 05.01.19.
//

#ifndef KALAMBURY_SERVER_DATASTORAGE_H
#define KALAMBURY_SERVER_DATASTORAGE_H

#include <vector>
#include <string>
#include "User.h"

class DataStorage {
    std::vector<User> users;
public:
    DataStorage();
    void addUser(User);

};


#endif //KALAMBURY_SERVER_DATASTORAGE_H
