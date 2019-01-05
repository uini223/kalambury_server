//
// Created by ramon on 05.01.19.
//

#ifndef KALAMBURY_SERVER_CONNECTIONINPUTHANDLER_H
#define KALAMBURY_SERVER_CONNECTIONINPUTHANDLER_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class ConnectionInputHandler {
    std::vector<std::string> messages;
    std::vector<int> fds;
    std::vector<int> msg_ids;
public:
    ConnectionInputHandler();
    void handleNewInput(std::string input, int fd);
};


#endif //KALAMBURY_SERVER_CONNECTIONINPUTHANDLER_H
