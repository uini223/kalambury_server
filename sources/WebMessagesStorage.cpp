//
// Created by Emil on 12/30/18.
//

#include "../headers/WebMessagesStorage.h"

void WebMessagesStorage::registerStorage(int fd) {
    this->fd_to_message[fd] = "";
}
