cmake_minimum_required(VERSION 3.25)
project(CPP)

set(CMAKE_CXX_STANDARD 11)

add_executable(CPP main.cpp VectorTest.h LinkedListTest.h LinkedListQueue.h
        Weijia/weijia_cpu.cpp)
