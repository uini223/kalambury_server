//
// Created by Emil on 12/28/18.
//

#ifndef KALAMBURY_SERVER_SERVER_H
#define KALAMBURY_SERVER_SERVER_H

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <error.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unordered_set>

class Server {
    int server_fd, epoll_fd;
    uint16_t port;
    std::string addr;
    std::unordered_set<int> clientFds;

public:
    Server(uint16_t port, const std::string &addr);

    virtual ~Server();

    void start();

private:
    void createServerSocket();
    void bindServerSocket();
    void enterListenMode();
    void setReuseAddr(int sock);
};


#endif //KALAMBURY_SERVER_SERVER_H
