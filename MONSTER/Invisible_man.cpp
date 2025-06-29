#include "Invisible_man.hpp"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>

using namespace std;

Invisible_man::Invisible_man(): Monster(1, "Invisible_man", {"Inn", "Bern", "Institute", "Laboratory", "Mansion"}){

    investigate["Inn"] = 1;
    investigate["Bern"] = 1;
    investigate["Institute"] = 1;
    investigate["Laboratory"] = 1;
    investigate["Mansion"] = 1;
};



bool Invisible_man::set_investigate_found(string place){

    if(investigate.count(place)){

        if(investigate[place]){
            
            investigate[place] = 0;
            return true;
        }

        return false;
    }

    else{

        throw invalid_argument("In this place there is no any Invisible_man item.");
    }
}
void Invisible_man::reset_near_villager(vector<Villager> villager){

    for(auto obj_villager : villager){

        if(near_villager.count(obj_villager)){

            near_villager[obj_villager] = 1;
        }

        else{

            near_villager[obj_villager] = 0;
        }
    }

    for(auto pair: near_villager){

        auto it = find_if(villager.begin(), villager.end(), [&](const Villager& V){return V.get_name() == pair.first.get_name();});

        if(it == villager.end()){

            near_villager.erase(pair.first);
        }
    }
}
bool Invisible_man::can_kill_villager(Villager villager){
    return near_villager.count(villager) && near_villager[villager];
}
bool Invisible_man::check_investigate() {
    return !investigate["Inn"] && !investigate["Bern"] && !investigate["Institute"] && !investigate["Laboratory"] && !investigate["Mansion"] ;
}
