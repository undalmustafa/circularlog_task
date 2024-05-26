cmake_minimum_required(VERSION 3.28)
project(CircularLogTask)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CircularLogTask
        Logger.cpp
        Logger.h)
