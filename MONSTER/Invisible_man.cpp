#include "Invisible_man.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

Invisible_man::Invisible_man(): Monster(1, "Invisible_man", {"Inn", "Bern", "Institute", "Laboratory", "Mansion"}){

    investigste["Inn"] = 1;
    investigste["Bern"] = 1;
    investigste["Institute"] = 1;
    investigste["Laboratory"] = 1;
    investigste["Mansion"] = 1;
};



bool Invisible_man::set_investigate_found(string place){

    if(investigate.count(place)){

        if(investigate[place]){
            
            investigate[place] = 0;
            return true
        }

        return false;
    }

    else{

        throw invalid_argument("In this place there is no any Invisible_man item.");
    }
}
void Invisible_man::reset_near_villager(vector<Villager> villager){

    for(auto obj_villager : villager){

        if(near_villager.count(obj_villager.name)){

            near_villager[obj_villager.name] = 1;
        }

        else{

            near_villager[obj_villager.name] = 0;
        }
    }

    for(auto pair: near_villager){

        auto it = find_if(villager.begin(), villager.end(), [&](const Villager& V){return V.name == pair.first;});

        if(!it){

            near_villager.erase(pair.first);
        }
    }
}
bool Invisible_man::can_kill_villager(Villager villager){
    return near_villager.count(villager) && near_villager[villager];
}