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
    if (temp.find(START) != -1) {
        temp.erase(0, START_LENGTH);
        packageStucture.message_id = this->getMessageId(temp);
        packageStucture.package_number = this->getPackageNumber(temp);
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

int WebMessageParser::getPackageNumber(std::string &data) {
    // int closing_bracket = data.find(']') + 1;
    std::string package_number_opening_str = data.substr(0, PACKAGE_NUMBER_LENGTH);
    // std::string package_number_closing_str = data.substr(closing_bracket, PACKAGE_NUMBER_LENGTH);
    int package_number_opening = std::stoi(package_number_opening_str);
    //    int package_number_opening =  0 ;
    //    int package_number_closing = 0 ;
    // int package_number_closing = std::stoi(package_number_closing_str);
    data.erase(0, PACKAGE_NUMBER_LENGTH);
    // data.erase(closing_bracket, PACKAGE_NUMBER_LENGTH);
    if (package_number_opening) {
        return package_number_opening;
    } else {
        return -1;
    }
}

int WebMessageParser::getMessageId(std::string &data) {
    std::string message_id = data.substr(0, ID_LENGTH);
    data.erase(0, ID_LENGTH);
    return std::stoi(message_id);
}
