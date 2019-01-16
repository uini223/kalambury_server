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
#include <vector>
#include "User.h"
#include "WebMessageParser.h"
#include "ConnectionInputHandler.h"

class Server {
    int server_fd, epoll_fd;
    uint16_t port;
    std::string addr;
    std::unordered_set<int> clientFds;
    struct epoll_event events[20];
    ConnectionInputHandler connectionInputHandler;

public:
    Server(uint16_t port, const std::string &addr);

    virtual ~Server();

    void start();
    void sendMessage(int fd, char data[],size_t size);
    void sendMessage(int fd, std::string data);
    void sendMessageToAllExceptOne(std::string, int);
    void sendMessageTo(std::vector<int>, std::string);
    void sendMessageToAll(std::string);

    void sendMessageToExceptOne(std::vector<int> &fds, std::string data, int fd);

private:
    void createServerSocket();
    void bindServerSocket();
    void enterListenMode();
    void acceptNewConnection();
    epoll_event createEvent(uint32_t eventType, int fd);
    void initEpoll();
    void addEvent(epoll_event event);
    void setReuseAddr(int sock);

};


#endif //KALAMBURY_SERVER_SERVER_H
