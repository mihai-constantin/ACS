cmake_minimum_required(VERSION 3.13)
project(p1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(p1
        complex.h
        main.cpp)
