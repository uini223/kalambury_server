//
// Created by Emil on 12/28/18.
//

#include "Server.h"
#include <functional>

void Server::setReuseAddr(int sock) {
    const int one = 1;
    int res = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if(res) error(1, errno, "setsockopt failed");
}

void Server::bindServerSocket() {
    sockaddr_in serverAddr{.sin_family=AF_INET, .sin_port=htons(this->port)};
    serverAddr.sin_addr.s_addr = inet_addr(this->addr.c_str());
    int res = bind(this->server_fd,(sockaddr*) &serverAddr, sizeof(serverAddr));
    if(res) error(1, errno, "bind failed");

}

void Server::createServerSocket() {
    this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) error(1, errno, "socket failed");
    this->setReuseAddr(this->server_fd);
}

Server::Server(uint16_t port, const std::string &addr) : port(port), addr(addr) {}

void Server::enterListenMode() {
    int res = listen(this->server_fd, 1);
    if(res) error(1, errno, "listen failed");
}

void Server::start() {
    this->createServerSocket();
    this->bindServerSocket();
    this->enterListenMode();
}

Server::~Server() {
    close(this->server_fd);
    printf("Closing server\n");
}
