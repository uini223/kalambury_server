#include <signal.h>
#include <stdio.h>
#include <iostream>
#include "Server.h"
#include "WebMessageParser.h"

Server *server;

void ctrl_c(int);
void testParser();

int main() {
    // catch ctrl+c signal and quit save
    signal(SIGINT, ctrl_c);

    testParser();
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

void testParser() {
    WebMessageParser parser;

    char start[255] = "START001";
    char data[255] = "001001[to jest wiadomość testowa dla parsera]";
    char s[255] = "001002[druga wiadomosc testowa]";
    PackageStucture structure = parser.parse(data);
    printf("Message_id = %d\npackage_id = %d\ndata = %s\n", structure.message_id,
           structure.package_number, structure.data.c_str());
    structure = parser.parse(s);
    printf("Message_id = %d\npackage_id = %d\ndata = %s\n", structure.message_id,
           structure.package_number, structure.data.c_str());
    structure = parser.parse(start);
    printf("Message_id = %d\npackage_id = %d\ndata = %s\n", structure.message_id,
           structure.package_number, structure.data.c_str());
}
