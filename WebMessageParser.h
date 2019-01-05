//
// Created by Emil on 12/30/18.
//

#ifndef KALAMBURY_SERVER_WEBMESSAGEPARSER_H
#define KALAMBURY_SERVER_WEBMESSAGEPARSER_H

#define START "START"
#define START_LENGTH 5
#define ID_LENGTH 3
#define PACKAGE_NUMBER_LENGTH 3
#define PACKAGE_DATA_SIZE 220
#define STOP "STOP"
#define STOP_LENGTH 4

#include <string>
#include <vector>
#include "PackageStucture.h"

class WebMessageParser {
      public:
       PackageStucture parse(char *data);
       std::vector<std::string> packString(std::string, int);
        int getPackageNumber(std::string &data);
        int getMessageId(std::string &data);
      private:
       std::string toString(int);
};

#endif  //KALAMBURY_SERVER_WEBMESSAGEPARSER_H
