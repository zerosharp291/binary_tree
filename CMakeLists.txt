cmake_minimum_required(VERSION 3.30)
project(binary_tree)

set(CMAKE_CXX_STANDARD 20)

add_executable(binary_tree src/main.cpp
        include/binary_tree.cpp
        include/binary_tree.h)
