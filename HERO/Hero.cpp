#include "Hero.hpp"
#include <iostream>
#include <sstream>

using namespace std;

Hero::Hero(string name, string spawn_and_now_place, bool special_action_info, int action): action(action), special_action_info(1){

    set_name(name);
    set_spawn_place(spawn_and_now_place);
    set_now_place(spawn_and_now_place);
    set_investigate_item();
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
void Hero::set_item(Item item_info){
    if(item.count(item_info)){
        item[item_info]++;
        return;
    }
    item[item_info] = 1;
}
void Hero::set_investigate_item(){

    Item temp(0);
    investigate_item["Inn"] = temp;
    investigate_item["Barn"] = temp;
    investigate_item["Institute"] = temp;
    investigate_item["Laboratory"] = temp;
    investigate_item["Mansion"] = temp;
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
shared_ptr<Perk> Hero::get_perk(){

    int counter{1};
    vector <shared_ptr<Perk>> vec;

    for(auto print: perk){

        cout << counter << '.' << (*print.first).get_name() << '   ';
        vec.push_back(print.first);
        counter++;
    }

    cout << counter << '.' << "exit";
    cout << "Please enter the number of perk you want: ";
    int choose;
    string ch;cin >> ch;
    istringstream iss(ch);

    if(iss >> choose && choose >= 1 && choose <= counter){

        if(choose == counter){

            return nullptr;//if player want to exit in this time func retrunes nullptr
        }

        perk[vec[choose - 1]]--;
        if(!perk[vec[choose - 1]]){

            perk.erase(vec[choose - 1]);
        }
    }
    else{

        throw invalid_argument("please enter a right value");
    }

    return vec[choose - 1];
}
vector <Item> Hero::get_item(string color, int strength){
    
    int sum_strength{};
    vector <Item> vec;

    for(auto obj_item: item){

        if(obj_item.first.get_color() == color){

            sum_strength += obj_item.first.get_strength();

            if(obj_item.second > 1){

               if(sum_strength >= strength)break;              
               sum_strength += obj_item.first.get_strength();
               vec.push_back(obj_item.first);
            }

            vec.push_back(obj_item.first);
        }

        if(sum_strength >= strength)break;
    }

    if(sum_strength < strength)return {};

    for(auto obj_item: vec){

        item[obj_item]--;

        if(!item[obj_item]){

            item.erase(obj_item);
        }
    }

    return vec;
}
unordered_map <std::string, Item> Hero::get_investigate_item()const{
    return investigate_item;
}



void Hero::Describe_Hero_Special_Action(){

cout << R"(
Archaologist: 
He can pick up any number of items from a nearby location.

Mayor:
She Has no special action.

)";
}
bool Hero::edit_investigate_item(Item item_info){

    if(investigate_item.count(item_info.get_spawn_place())){

        return false;
    }
    investigate_item[item_info.get_spawn_place()] = item_info;
    return true;
}