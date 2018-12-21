cmake_minimum_required(VERSION 3.12)
project(Project_3Duck)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project_3Duck
        linearList.h
        main.cpp
        queue.h)
