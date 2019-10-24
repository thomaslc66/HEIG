cmake_minimum_required(VERSION 2.8.8)
project(DLinkedList)

set(CMAKE_CXX_STANDARD 11)

add_executable(DLinkedList main.cpp List.h ListImpl.hpp Person.cpp Child.cpp)