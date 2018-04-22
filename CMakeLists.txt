cmake_minimum_required(VERSION 3.10)
project(signalk)

set(CMAKE_CXX_STANDARD 11)

include_directories(core)

add_executable(signalktest
        core/DataBase.cpp
        core/DataBase.h
        core/json.hpp
        core/ReaderHandler.h
        core/variant.h
        test/main.cpp)
