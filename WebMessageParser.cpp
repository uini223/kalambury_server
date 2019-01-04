//
// Created by Emil on 12/30/18.
//
#include "WebMessageParser.h"
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

PackageStucture WebMessageParser::parse(char *data) {
    std::string temp(data);
    PackageStucture packageStucture;
    if (temp.find(START) != -1 || temp.find(STOP) != -1) {
        packageStucture.message_id = this->getMessageId(temp);
        packageStucture.package_number = NULL;
        packageStucture.data = "";
    } else {
        packageStucture.message_id = this->getMessageId(temp);
        packageStucture.package_number = this->getPackageNumber(temp);
        int package_data_start = temp.find('[');
        int package_data_end = temp.find(']');
        packageStucture.data = temp.substr(package_data_start + 1, package_data_end - 1);
    }
    return packageStucture;
}

std::vector<std::string> WebMessageParser::packString(std::string data, int msg_id) {
    std::vector<PackageStucture> pckg_list;
    std::vector<std::string> out_list;
    PackageStucture pom;
    pom.message_id = msg_id;
    int package_counter = 0;

    for (int i = 0; i < data.length(); i += PACKAGE_DATA_SIZE) {
        if (i == 0) {
            pom.data = "START";
            pom.package_number = package_counter;
            package_counter++;
            pckg_list.push_back(pom);
        }

        if (i * PACKAGE_DATA_SIZE + PACKAGE_DATA_SIZE > data.length()) {
            pom.data = data.substr(i * PACKAGE_DATA_SIZE, data.length());
            pom.package_number = package_counter;
            pckg_list.push_back(pom);
            package_counter++;

            pom.data = "STOP";
            pom.package_number = package_counter;
            pckg_list.push_back(pom);
            break;
        } else {
            pom.data = data.substr(i, PACKAGE_DATA_SIZE);
            pom.package_number = package_counter;
            package_counter++;
            pckg_list.push_back(pom);
        }
    }
    for (auto var : pckg_list) {
        if (var.data.find("START") != std::string::npos || var.data.find("STOP") != std::string::npos) {
            out_list.push_back(var.data + toString(var.message_id) + toString(var.package_number));
        } else {
            out_list.push_back(toString(var.message_id) + toString(var.package_number) + "[" + var.data + "]");
        }
    }

    return out_list;
}

int WebMessageParser::getPackageNumber(std::string &data) {
    std::string package_number_opening_str = data.substr(0, PACKAGE_NUMBER_LENGTH);
    int package_number_opening = std::stoi(package_number_opening_str);
    data.erase(0, PACKAGE_NUMBER_LENGTH);
    if (package_number_opening) {
        return package_number_opening;
    } else {
        return -1;
    }
}

int WebMessageParser::getMessageId(std::string &data) {
    std::string message_id = "";
    if (data.find(START) != -1) {
        message_id = data.substr(START_LENGTH, ID_LENGTH);
        data.erase(ID_LENGTH, START_LENGTH);

    } else if (data.find(STOP) != -1) {
        message_id = data.substr(STOP_LENGTH, ID_LENGTH);
        data.erase(ID_LENGTH, STOP_LENGTH);

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
