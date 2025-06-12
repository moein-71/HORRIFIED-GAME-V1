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



bool Map::Kill_Villager(string place){

    if(villager_place[place].size() >= 1){

        villager_place[place].erase(villager_place[place].begin());
        if(!villager_place[place].size()){
            villager_place.erase(place);
        }
        return true;
    }
    else{
        return false;
    }
}
Item Map::Pickeup_Item(string place, string item_name){

    for(auto item: item_place[place]){
        if(item.first.get_name() == item_name){

            item_place[place][item.first]--;

            if(!item_place[place][item.first]){
                item_place[place].erase(item.first);
            }           
            return item.first;
        }
    }
} 
string Map::Find_Place_With_More_Item(){

    int counter{};
    int max{-1};
    string res_place;
    
    for(auto place_name: item_place){

        counter = 0;
        for(auto item: place_name.second){
            counter += item.second;
        }
        if(max < counter){

            max = counter;
            res_place = place_name.first;
        }
    }

    return res_place;
}
vector<pair<Item, int>> Map::Remove_All_Item_In_Place(string place){

    vector<pair<Item, int>> res;
    for(auto item: item_place[place]){
        res.push_back({item.first, item.second});
    }
    item_place.erase(place);
    return res;
}