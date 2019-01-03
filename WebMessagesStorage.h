//
// Created by Emil on 12/30/18.
//

#ifndef KALAMBURY_SERVER_WEBMESSAGESSTORAGE_H
#define KALAMBURY_SERVER_WEBMESSAGESSTORAGE_H

#include <map>

class WebMessagesStorage {
    std::map<int, std::string> fd_to_message;
public:
    void registerStorage(int fd);
};


#endif //KALAMBURY_SERVER_WEBMESSAGESSTORAGE_H
