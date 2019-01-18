#include <signal.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "../headers/Server.h"
#include "../headers/WebMessageParser.h"

Server *server;

void ctrl_c(int);

int main() {
    // catch ctrl+c signal and quit save
    signal(SIGINT, ctrl_c);
    signal(SIGABRT, ctrl_c);
    signal(SIGTERM, ctrl_c);
    signal(SIGQUIT, ctrl_c);

    // std::ifstream config;
    // config.open("../config.txt");
    // std::string data;
    // std::string buf;
    // while(getline(config, data)) {
    //     getline(config, buf);
    //     data += buf;
    // }
    // config.close();
    // rapidjson::Document d;
    // d.Parse(data.c_str());
    // std::string serverAddress = d["address"].GetString();
    // int serverPort = d["port"].GetInt();

    //    new server instance (port, ipv4 address)
    server = new Server((uint16_t)(20000), "127.0.0.1");
    // start running server
    server->start();

    return 0;
}

void ctrl_c(int) {
    delete server;
    exit(0);
}
