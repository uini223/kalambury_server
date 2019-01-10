//
// Created by ramon on 05.01.19.
//

#include "../headers/User.h"

User::User(int id, const std::string &name) : id(id), name(name) {
    this->id = id;
    this->name = name;
}

std::string User::toString() {
    return R"(", "name": ")" + name + "\"}";
}

int User::getId() {
    return id;
}

std::string User::getName() {
    return name;
}

User::User() = default;

User::~User() = default;
