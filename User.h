//
// Created by ramon on 05.01.19.
//

#ifndef KALAMBURY_SERVER_USER_H
#define KALAMBURY_SERVER_USER_H

#include <string>


class User {
    int id;
    std::string name;
public:
    User(int id, const std::string &name);

    virtual ~User();

};


#endif //KALAMBURY_SERVER_USER_H
