cmake_minimum_required(VERSION 3.10)
project(kalambury_server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -Wall)

add_executable(kalambury_server sources/main.cpp sources/Server.cpp headers/Server.h headers/WebMessagesStorage.h sources/WebMessageParser.cpp headers/WebMessageParser.h sources/User.cpp headers/User.h sources/ConnectionInputHandler.cpp headers/ConnectionInputHandler.h sources/DataStorage.cpp headers/DataStorage.h headers/RoomData.h sources/RoomData.cpp sources/AbstractData.cpp headers/AbstractData.h sources/ChatMessage.cpp headers/ChatMessage.h)