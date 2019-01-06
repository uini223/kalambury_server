#include <signal.h>
#include <stdio.h>
#include <iostream>
#include "headers/Server.h"
#include "headers/WebMessageParser.h"

Server *server;

void ctrl_c(int);
void testParser();

int main() {
    // catch ctrl+c signal and quit save
    signal(SIGINT, ctrl_c);

    // testParser();
    //    new server instance (port, ipv4 address)
    server = new Server(20000, "127.0.0.1");
    // start running server
    server->start();

    return 0;
}

void ctrl_c(int) {
    delete server;
    exit(0);
}
