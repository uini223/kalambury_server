//
// Created by Emil on 12/28/18.
//

#include "../headers/Server.h"
#include <fcntl.h>

void Server::setReuseAddr(int sock) {
    const int one = 1;
    int res = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    if (res) error(1, errno, "setsockopt failed");
}

void Server::bindServerSocket() {
    sockaddr_in serverAddr{.sin_family = AF_INET, .sin_port = htons(this->port)};
    serverAddr.sin_addr.s_addr = inet_addr(this->addr.c_str());
    int res = bind(this->server_fd, (sockaddr *)&serverAddr, sizeof(serverAddr));
    if (res) error(1, errno, "bind failed");
    printf("Binded address to server \n");
}

void Server::createServerSocket() {
    this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) error(1, errno, "socket failed");
    this->setReuseAddr(this->server_fd);
    printf("Created server socket \n");
}

Server::Server(uint16_t port, const std::string &addr) : port(port), addr(addr) {
    this->initEpoll();
    this->createServerSocket();
    this->bindServerSocket();
    this->connectionInputHandler.setServer(this);
}

void Server::enterListenMode() {
    int res = listen(this->server_fd, 1);
    if (res) error(1, errno, "listen failed");
    this->addEvent(createEvent(EPOLLIN, this->server_fd));
    printf("Listening on addr %s port %d \n", this->addr.c_str(), this->port);
}

void Server::start() {
    this->enterListenMode();
    this->addEvent(createEvent(EPOLLIN, 0));
    int event_count = 0;
    char read_buff[255];
    while (true) {
        event_count = epoll_wait(this->epoll_fd, this->events, sizeof(this->events), -1);
        for (int i = 0; i < event_count; i++) {
            if (events[i].data.fd == this->server_fd) {
                this->acceptNewConnection();
            } else if (events[i].data.fd == 0) {
                ssize_t bytes_read = read(0, read_buff, 255);
                for (int client_fd : this->clientFds) {
                    this->sendMessage(client_fd, read_buff, (size_t)bytes_read);
                }
            } else {
                auto fd = events[i].data.fd;
                ssize_t bytes_read = read(fd, read_buff, 255);
                if (bytes_read < 1) {
                    printf("Client with fd=%d disconnected \n", fd);
                    clientFds.erase(fd);
                    close(fd);
                    this->connectionInputHandler.handleUserQuit(fd);
                    continue;
                } else {
                    printf("%zd bytes read.\n", bytes_read);
                    printf("Read '%s'\n", read_buff);
                    connectionInputHandler.handleNewInput(fd, read_buff);
                }
            }
            bzero(read_buff, sizeof(read_buff));
        }
    }
}

void Server::sendMessageTo(std::vector<int> clients, std::string message) {
    for (auto client: clients) {
        sendMessage(client, message);
    }
}

Server::~Server() {
    close(this->server_fd);
    close(this->epoll_fd);
    for (int client_fd : clientFds)
        close(client_fd);
    printf("Closing server\n");
}

void Server::initEpoll() {
    this->epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) error(1, errno, "initiating epoll failed");
    printf("Initiated epoll!\n");
}

void Server::addEvent(epoll_event event) {
    if (epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, event.data.fd, &event)) {
        error(1, errno, "adding new event to control failed");
    }
}

void Server::acceptNewConnection() {
    int client_fd;
    sockaddr_in client_addr{0};
    socklen_t client_addr_size = sizeof(client_addr);
    client_fd = accept(this->server_fd, (sockaddr *)&client_addr, &client_addr_size);
    if (client_fd == -1) error(1, errno, "accept failed");
    this->clientFds.insert(client_fd);
    printf("New connection from: %s:%hu (fd: %d)\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port),
           client_fd);
    this->addEvent(this->createEvent(EPOLLIN, client_fd));
    fcntl(client_fd, F_SETFL, O_NONBLOCK);
}

epoll_event Server::createEvent(uint32_t eventType, int fd) {
    struct epoll_event event{};
    event.events = eventType;
    event.data.fd = fd;
    printf("New event control created for fd=%d \n", fd);
    return event;
}

void Server::sendMessage(int fd, char *data, size_t size) {
    auto res = write(fd, data, size);
    printf("Sent %zi bytes to fd=%d\ncontent: %s\n", res, fd, data);
}

void Server::sendMessage(int fd, std::string data) {
    size_t size1 = 0;
    std::string temp;
    while(data.length() > 0) {
        if(data.length() > 255) {
            size1 = 255;
            temp = data.substr(0, 255);
        } else {
            size1 = data.length();
            temp = data;
        }
        data.erase(0, size1);
        char *buff = new char[size1+1];
        strcpy(buff,temp.c_str());
        sendMessage(fd, buff, size1);
    }
}

void Server::sendMessageToAllExceptOne(std::string message, int fd) {
    for (auto clientFd: this->clientFds) {
            if(clientFd != fd) {
                char* pom = new char[message.length()+1];
                strcpy(pom, message.c_str());
                sendMessage(clientFd, pom, message.length());
                delete []pom;
            }
    }
}

void Server::sendMessageToExceptOne(std::vector<int> &fds, std::string data, int fd) {
    for(auto clientFd: fds) {
        if(clientFd != fd) {
            sendMessage(clientFd, data);
        }
    }
}
