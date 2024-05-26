cmake_minimum_required(VERSION 3.28)
project(CircularLogTask)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(CircularLogTask
        src/Logger.cpp
        src/Logger.h
        src/main.cpp)
