//
// Created by ramon on 05.01.19.
//

#include "../headers/User.h"

User::User(int id, const std::string &name) : id(id), name(name) {
    this->id = id;
    this->name = name;
}

std::string User::toString() {
    return R"({id" : ")" + std::to_string(id) + R"(", "name": ")" + name + "\"}";
}

User::~User() = default;
