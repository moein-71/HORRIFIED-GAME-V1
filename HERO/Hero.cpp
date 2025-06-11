#include "Hero.hpp"
#include <iostream>

using namespace std;

Hero::Hero(string name, string spawn_and_now_place, bool special_action_info, int action): action(action){

    set_name(name);
    set_spawn_place(spawn_and_now_place);
    set_now_place(spawn_and_now_place);
    set_special_action_info(special_action_info);
}



void Hero::set_special_action_info(bool special_action_info){
    this -> special_action_info = special_action_info;
}
void Hero::set_name(string name){
    this -> name = name;
}
void Hero::set_player_name(string player_name){
    this -> player_name = player_name;
}
void Hero::set_spawn_place(string spawn_place){
    this -> spawn_place = spawn_place;
}
void Hero::set_now_place(string now_place){
    this -> now_place = now_place;
}



bool Hero::get_special_action_info()const{
    return special_action_info;
}
int Hero::get_action()const{
    return action;
}
string Hero::get_name()const{
    return name;
}
string Hero::get_player_name()const{
    return player_name;
}
string Hero::get_spawn_place()const{
    return spawn_place;
}
string Hero::get_now_place()const{
    return now_place;
}



void Hero::Describe_Hero_Special_Action(){

cout << R"(
Archaologist: 
He can pick up any number of items from a nearby location.

Mayor:
She Has no special action.

)";
}