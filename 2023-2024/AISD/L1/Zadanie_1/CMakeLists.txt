cmake_minimum_required(VERSION 3.27)
project(L1)

set(CMAKE_CXX_STANDARD 17)

add_executable(L1 main.cpp
        Queue.cpp
        Queue.hpp
        Stack.cpp
        Stack.hpp)
