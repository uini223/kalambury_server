//
// Created by Emil on 12/30/18.
//

#ifndef KALAMBURY_SERVER_WEBMESSAGEPARSER_H
#define KALAMBURY_SERVER_WEBMESSAGEPARSER_H

#define START "START"
#define START_LENGTH 5
#define ID_LENGTH 3
#define PACKAGE_DATA_SIZE 220
#define STOP "STOP"
#define STOP_LENGTH 4

#include <string>
#include <vector>
#include "PackageStucture.h"

class WebMessageParser {
      public:
       std::string parse(std::string data);
       std::vector<std::string> packString(std::string, int);
        int getMessageId(std::string &data);
      private:
       std::string toString(int);
       void eraseStart(std::string &data);
       void eraseStop(std::string &data);
};

#endif  //KALAMBURY_SERVER_WEBMESSAGEPARSER_H
