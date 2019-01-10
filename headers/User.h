//
// Created by ramon on 05.01.19.
//

#ifndef KALAMBURY_SERVER_USER_H
#define KALAMBURY_SERVER_USER_H

#include <string>
#include "AbstractData.h"


class User: AbstractData {
    int id;
    std::string name;
public:
    User();

    User(int id, const std::string &name);
    virtual ~User();
    std::string toString() override;

    int getId();

    std::string getName();

};


#endif //KALAMBURY_SERVER_USER_H
