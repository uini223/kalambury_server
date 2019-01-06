//
// Created by ramon on 05.01.19.
//

#include "../headers/DataStorage.h"

DataStorage::DataStorage() {}

void DataStorage::addUser(User user) {
    this->users.push_back(user);
}
