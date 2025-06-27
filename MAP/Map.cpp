#include "Map.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>
#include <vector>
#include <optional>
#include <algorithm>
#include <climits>

using namespace std;

Map::Map(){

    set_connection();
}
vector<Villager> Map::get_villager(string place){
    return villager_place[place];
}



void Map::set_connection(){

    connection["Crypt"] = {"Abbey"};
    connection["Museum"] = {"Shop", "Church", "Mansion"};
    connection["Church"] = {"Museum", "Hospital", "Shop", "Graveyard", "Mansion"};
    connection["Hospital"] = {"Church"};
    connection["Graveyard"] = {"Church"};
    connection["Institute"] = {"Laboratory"};
    connection["Docks"] = {"Tower"};
    connection["Tower"] = {"Docks", "Dungeon", "Theatre"};
    connection["Dungeon"] = {"Tower"};
    connection["Inn"] = {"Camp", "Precinct", "Mansion", "Theatre"};
    connection["Precinct"] = {"Inn", "Camp", "Theatre", "Mansion"};
    connection["Camp"] = {"Precinct", "Cave", "Mansion", "Theatre", "Inn"};
    connection["Cave"] = {"Camp"};
    connection["Theatre"] = {"Tower", "Bank", "Shop", "Precinct", "Mansion", "Inn", "Camp"};
    connection["Shop"] = {"Theatre", "Church", "Laboratory"};
    connection["Laboratory"] = {"Shop", "Institute"};
    connection["Abbey"] = {"Mansion", "Crypt"};
    connection["Mansion"] = {"Abbey", "Camp", "Inn", "Theatre", "Precinct", "Shop", "Museum", "Church"};
    connection["Bank"] = {"Theatre"};
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
string Map::Find_Near_Destination(int max_steps, string current_location, Archaologist archaologist, Mayor mayor){

    unordered_map<std::string, std::string> parent;
    unordered_map<std::string, int> distance;
    queue<std::string> q;
    unordered_set<std::string> visited;

    q.push(current_location);
    distance[current_location] = 0;
    visited.insert(current_location);

    string archaologist_loc = archaologist.get_now_place();
    string mayor_loc = mayor.get_now_place();

    vector<std::string> candidates;
    int min_dist = -1;

    while (!q.empty()){

        std::string node = q.front(); q.pop();
        int d = distance[node];

        bool is_hero = (node == archaologist_loc || node == mayor_loc);
        bool has_villager = (villager_place.count(node) && !villager_place.at(node).empty());

        if (is_hero || has_villager){

            if (min_dist == -1){
                min_dist = d;
                candidates.push_back(node);
            } 
            
            else if (d == min_dist)
                candidates.push_back(node);

            else if (d > min_dist) 
                break;
            
        }

        for(const string& neighbor : connection[node]){

            if(!visited.count(neighbor)){

                visited.insert(neighbor);
                parent[neighbor] = node;
                distance[neighbor] = d + 1;
                q.push(neighbor);
            }
        }
    }

    if (candidates.empty()) return current_location;

    string best_target = candidates[0];
    int best_villager_count = villager_place.count(best_target) ? villager_place[best_target].size() : 0;
    bool best_is_hero = (best_target == archaologist_loc || best_target == mayor_loc);

    for(const std::string& loc : candidates){

        bool is_hero = (loc == archaologist_loc || loc == mayor_loc);
        int villager_count = villager_place.count(loc) ? villager_place[loc].size() : 0;

        if(is_hero && !best_is_hero){

            best_target = loc;
            best_villager_count = villager_count;
            best_is_hero = true;
        } 
        else if(is_hero == best_is_hero){

            if (villager_count > best_villager_count){
                best_target = loc;
                best_villager_count = villager_count;
            }
        }
    }

    vector<std::string> path;
    string current = best_target;

    while(current != current_location){
        path.push_back(current);
        current = parent[current];
    }

    reverse(path.begin(), path.end());

    if((int)path.size() <= max_steps)
        return best_target;

    else{

        if(max_steps == 0 || path.empty())
            return current_location;
        return path[max_steps - 1];
    }
}
string Map::Move_Monster_Away_From_Hero(string current_location, Hero* target_hero, Hero* other_hero) {

    const int max_steps = 2;  
    unordered_map<string, string> parent;
    unordered_map<string, int> distance;
    queue<string> q;
    unordered_set<string> visited;

    q.push(target_hero->get_now_place());
    distance[target_hero->get_now_place()] = 0;
    visited.insert(target_hero->get_now_place());

    while(!q.empty()){

        string node = q.front(); q.pop();
        int d = distance[node];

        for(const string& neighbor : connection[node]){
            if(!visited.count(neighbor)){

                visited.insert(neighbor);
                parent[neighbor] = node;
                distance[neighbor] = d + 1;
                q.push(neighbor);
            }
        }
    }

    if (!distance.count(current_location))
        return current_location;

    queue<pair<string, int>> q2;
    unordered_set<string> visited2;

    q2.push({current_location, 0});
    visited2.insert(current_location);

    vector<string> candidates;
    int best_distance = distance[current_location]; 

    while(!q2.empty()){

        auto [node, steps] = q2.front(); q2.pop();

        if(distance.count(node) && distance[node] > best_distance){
            candidates.push_back(node);
            continue;
        }

        if(steps == max_steps)
            continue; 

        for (const string& neighbor : connection[node]) {
            if (!visited2.count(neighbor)) {
                visited2.insert(neighbor);
                q2.push({neighbor, steps + 1});
            }
        }
    }

    if (candidates.empty()) 
        return current_location;

    auto is_close_to_villager = [&](const string& loc) -> bool {
        if (villager_place.count(loc) && !villager_place[loc].empty())
            return true;
            
        for (const string& neighbor : connection[loc]) {
            if (villager_place.count(neighbor) && !villager_place[neighbor].empty())
                return true;
        }
        return false;
    };

    auto hero_distance = [&](const string& loc, const string& hero_loc) -> int {
        if (distance.count(loc) && distance.count(hero_loc))
            return abs(distance[loc] - distance[hero_loc]);
        return INT_MAX;
    };

    string best_location = candidates[0];
    bool best_close_to_villager = is_close_to_villager(best_location);

    for(const string& cand : candidates){
        bool close_to_villager = is_close_to_villager(cand);

        if (!close_to_villager && best_close_to_villager) {
            best_location = cand;
            best_close_to_villager = false;
        }
        else if(close_to_villager == best_close_to_villager){

            int dist_best = hero_distance(best_location, other_hero->get_now_place());
            int dist_cand = hero_distance(cand, other_hero->get_now_place());
            if(dist_cand > dist_best){
                best_location = cand;
            }
        }
    }
    return best_location;
}

