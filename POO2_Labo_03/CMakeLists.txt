cmake_minimum_required(VERSION 3.6)
project(POO2_Labo_03)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/DoublyLinkedList.h src/DoublyLinkedListImpl.h src/DoublyLinkedList.h src/DoublyLinkedListImpl.h src/Node.h src/NodeImpl.h)

include_directories(src)
add_executable(POO2_Labo_03 ${SOURCE_FILES})