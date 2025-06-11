#include "Monster.hpp"
#include <iostream>
#include <ctime>

using namespace std;

Monster::Monster(int frenzy, string name, vector<string>const spawn_place): frenzy(frenzy),
 name(name), spawn_place(spawn_place){

    srand(std::time(0));
    int random = rand()%spawn_place.size();

    set_now_place(spawn_place[random]);
 }



int Monster::get_frenzy()const{
    return frenzy;
}
string Monster::get_name()const{
    return name;
}
string Monster::get_now_place()const{
    return now_place;
}
vector <string> Monster::get_spawn_place()const{
    return spawn_place;
}



void Monster::set_now_place(string now_place){
    this -> now_place = now_place;
}