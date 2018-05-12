cmake_minimum_required(VERSION 3.10)
project(DataStructures_HW1)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Werror -pedantic")

add_executable(DataStructures_HW1 AVLTree.h exceptions.h testMacros.h library1.h
        Oasis.cpp Oasis.h oasistest.cpp library1.cpp)
