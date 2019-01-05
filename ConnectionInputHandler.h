//
// Created by ramon on 05.01.19.
//

#ifndef KALAMBURY_SERVER_CONNECTIONINPUTHANDLER_H
#define KALAMBURY_SERVER_CONNECTIONINPUTHANDLER_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <map>

class ConnectionInputHandler {
    std::map<int, std::map<int, std::string>> fds_with_messages;
public:
    ConnectionInputHandler();
    void handleNewInput(std::string input, int fd);
};


#endif //KALAMBURY_SERVER_CONNECTIONINPUTHANDLER_H
