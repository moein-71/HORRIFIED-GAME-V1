#include "Map.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

Map::Map(){

    set_connection();
}
vector<Villager> Map::get_villager(string place){
    return villager_place[place];
}



void Map::set_connection(){

    connection["Crypt"] = {"Museum"};
    connection["Museum"] = {"Crypt", "Church"};
    connection["Church"] = {"Museum", "Hospital", "Shop", "Graveyard"};
    connection["Hospital"] = {"Church", "Mansion"};
    connection["Graveyard"] = {"Church", "Institute"};
    connection["Institute"] = {"Graveyard", "Waterfront"};
    connection["Waterfront"] = {"Institute", "Docks"};
    connection["Docks"] = {"Waterfront", "Tower"};
    connection["Tower"] = {"Docks", "Dungeon", "Theatre"};
    connection["Dungeon"] = {"Tower", "Barn"};
    connection["Barn"] = {"Dungeon", "Inn"};
    connection["Inn"] = {"Barn", "Precinct"};
    connection["Precinct"] = {"Inn", "Camp", "Theatre"};
    connection["Camp"] = {"Precinct", "Cave"};
    connection["Cave"] = {"Camp", "Lagoon"};
    connection["Lagoon"] = {"Cave"};
    connection["Theatre"] = {"Tower", "Precinct", "Shop"};
    connection["Shop"] = {"Theatre", "Church", "Laboratory"};
    connection["Laboratory"] = {"Shop"};
    connection["Abbey"] = {"Mansion"};
    connection["Mansion"] = {"Abbey", "Hospital"};
}
void Map::set_item(Item inf_item){
    item_place[inf_item.get_spawn_place()][inf_item]++;
}
void Map::set_villager(string place, Villager villager){
    villager_place[place].push_back(villager);
}
void Map::set_villager_place(string place, string villager_name){
    
    for(auto &villager: villager_place[place]){

        if(villager.get_name() == villager_name){

            villager.set_now_place(place);
            break;
        }
    }
}