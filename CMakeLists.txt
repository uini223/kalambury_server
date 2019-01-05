cmake_minimum_required(VERSION 3.10)
project(kalambury_server)

set(CMAKE_CXX_STANDARD 14)

add_executable(kalambury_server main.cpp Server.cpp Server.h WebMessagesStorage.cpp WebMessagesStorage.h WebMessageParser.cpp WebMessageParser.h PackageStucture.cpp PackageStucture.h User.cpp User.h ConnectionInputHandler.cpp ConnectionInputHandler.h)