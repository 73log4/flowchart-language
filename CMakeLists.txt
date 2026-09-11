cmake_minimum_required(VERSION 4.1)
project(flowchart_language)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(flowchart_language
        Interpreter.cpp
        Interpreter.h
        main.cpp
        CMD.cpp
        CMD.h)
