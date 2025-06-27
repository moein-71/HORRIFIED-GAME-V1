cmake_minimum_required(VERSION 3.5)

project(fact)

#set(CMAKE_CXX_STANDARD 14) for using version 14 compiler and now every one can use it 

add_executable(app ../src/main.cpp)

include_directories(../include ../Game ../Game_turn ../Game_turn/Turn_archaeologist ../Game_turn/Turn_mayor ../Game_turn/Turn_monster 
../Monster_action ../Monster_action/Kill ../Monster_action/Move_monster ../Monster_action/Power ../Monster_card ../Monster_card/card 
../Perk_card ../Perk_card/card )
