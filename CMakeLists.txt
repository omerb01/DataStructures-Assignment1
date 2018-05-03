cmake_minimum_required(VERSION 3.10)
project(DataStructures_HW1)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror -pedantic")

add_executable(DataStructures_HW1 main.cpp AVLTree.h)