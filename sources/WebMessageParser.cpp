//
// Created by Emil on 12/30/18.
//
#include "../headers/WebMessageParser.h"
#include <iostream>
#include "../libs/rapidjson/document.h"
#include "../libs/rapidjson/stringbuffer.h"
#include "../libs/rapidjson/writer.h"

// TODO this might return packageStructure to discuse
std::string WebMessageParser::parse(std::string data) {
    PackageStucture packageStucture;
    std::string content = "";
    this->eraseStart(data);
    this->eraseStop(data);
    auto openBracket = data.find('[');
    auto closeBracket = data.find(']');
    while (openBracket != -std::string::npos && closeBracket != std::string::npos) {
        content += data.substr(openBracket+1, closeBracket-openBracket-1);
        data.erase(openBracket, closeBracket-openBracket+1);
        openBracket = data.find('[');
        closeBracket = data.find(']');
    }
    return content;
}

//  TODO change that method to pack correctly
std::vector<std::string> WebMessageParser::packString(std::string data, int msg_id) {
    std::vector<PackageStucture> pckg_list;
    std::vector<std::string> out_list;
    PackageStucture pom;
    pom.message_id = msg_id;
    int package_counter = 0;

    for (int i = 0; i < data.length(); i += PACKAGE_DATA_SIZE) {
        if (i == 0) {
            pom.data = "START";
            package_counter++;
            pckg_list.push_back(pom);
        }

        if (i * PACKAGE_DATA_SIZE + PACKAGE_DATA_SIZE > data.length()) {
            pom.data = data.substr(i * PACKAGE_DATA_SIZE, data.length());
            pckg_list.push_back(pom);
            package_counter++;

            pom.data = "STOP";
            pckg_list.push_back(pom);
            break;
        } else {
            pom.data = data.substr(i, PACKAGE_DATA_SIZE);
            package_counter++;
            pckg_list.push_back(pom);
        }
    }
    for (auto var : pckg_list) {
        if (var.data.find("START") != std::string::npos || var.data.find("STOP") != std::string::npos) {
            out_list.push_back(var.data + toString(var.message_id));
        } else {
            out_list.push_back(toString(var.message_id) + "[" + var.data + "]");
        }
    }

    return out_list;
}

int WebMessageParser::getMessageId(std::string &data) {
    std::string message_id;
    auto findStart = data.find(START);
    auto findStop = data.find(STOP);
    if (findStart != -1) {
        message_id = data.substr(findStart + START_LENGTH, ID_LENGTH);
        data.erase(findStart + START_LENGTH, ID_LENGTH);

    } else if (findStop != -1) {
        message_id = data.substr(findStop + STOP_LENGTH, ID_LENGTH);
        data.erase(findStop + STOP_LENGTH, ID_LENGTH);

    } else {
        message_id = data.substr(0, ID_LENGTH);
        data.erase(0, ID_LENGTH);
    }
    return std::stoi(message_id);
}

std::string WebMessageParser::toString(int number) {
    switch (std::to_string(number).length()) {
        case 1:
            return "00" + std::to_string(number);
        case 2:
            return "0" + std::to_string(number);
        case 3:
            return std::to_string(number);
    }
}

void WebMessageParser::eraseStart(std::string &data) {
    data.erase(data.find(START), START_LENGTH);
}

void WebMessageParser::eraseStop(std::string &data) {
    data.erase(data.find(STOP), STOP_LENGTH);
}
