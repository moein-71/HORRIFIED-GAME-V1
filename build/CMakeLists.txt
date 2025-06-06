cmake_minimum_required(VERSION 3.5)

project(fact)

#set(CMAKE_CXX_STANDARD 14) for using version 14 compiler and now every one can use it 

add_executable(app ../src/main.cpp)

include_directories(../include)
