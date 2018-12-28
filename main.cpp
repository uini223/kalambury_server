#define MAX_EVENTS 5

#include <iostream>
#include <stdio.h>
#include <signal.h>
#include "Server.h"

#define PORT 2000

Server *server;

void ctrl_c(int);

int main() {

    signal(SIGINT, ctrl_c);

    server = new Server(2000, "127.0.0.1");
    server->start();
    while(true);


    return 0;
}

void ctrl_c(int) {
    delete server;
    exit(0);
}
