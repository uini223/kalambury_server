cmake_minimum_required(VERSION 3.12)
project(kalambury_server)

set(CMAKE_CXX_STANDARD 14)

add_executable(kalambury_server main.cpp Server.cpp Server.h temp.cpp)