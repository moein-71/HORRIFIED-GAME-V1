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
#include <limits>

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
bool Map::set_villager_place(string now_place, string new_place, string villager_name){
    
    auto& villager_now_place = villager_place[now_place];
    
    for(int i{}; i < villager_now_place.size(); ++i){
        if(villager_now_place[i].get_name() == villager_name){

            villager_now_place[i].set_now_place(new_place);
            set_villager(new_place, villager_now_place[i]);
            villager_now_place.erase(villager_now_place.begin() + i);
            return true;
        }
    }
    return false;
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
int Map::bfs_distance(const string& start, const string& goal){

    if (start == goal) return 0;

    unordered_set<string> visited;
    queue<pair<string, int>> q;
    q.push({start, 0});
    visited.insert(start);

    while(!q.empty()){

        auto [node, dist] = q.front(); q.pop();

        for(const auto& nbr : connection[node]){

            if (visited.count(nbr)) continue;
            if (nbr == goal) return dist + 1;
            visited.insert(nbr);
            q.push({nbr, dist + 1});
        }
    }
    return numeric_limits<int>::max();
}
string Map::Move_Hero_Away_From_Monsters(

    const string& current_hero_location,
    const string& first_monster_location,
    const string& second_monster_location,
    const string& other_hero_location,
    const int max_steps = 2)
{
    
    auto bfs_distance = [&](const string& start) -> unordered_map<string, int> {
        unordered_map<string, int> dist;
        queue<string> q;
        q.push(start);
        dist[start] = 0;

        while(!q.empty()){
            string node = q.front(); q.pop();
            int d = dist[node];
            for(const auto& neighbor : connection[node]){
                if(dist.find(neighbor) == dist.end()){
                    dist[neighbor] = d + 1;
                    q.push(neighbor);
                }
            }
        }
        return dist;
    };

    auto dist_first_monster = bfs_distance(first_monster_location);
    auto dist_second_monster = bfs_distance(second_monster_location);

    unordered_map<string, int> villager_distance;
    {
        vector<string> villager_places;
        for(const auto& [place, villagers] : villager_place) {
            if(!villagers.empty())
                villager_places.push_back(place);
        }

        if(villager_places.empty()){
            for(const auto& [place, _] : connection) {
                villager_distance[place] = INT_MAX;
            }
        } 
        else {
        
            queue<string> q;
            unordered_set<string> visited;
            for(const auto& vp : villager_places) {
                villager_distance[vp] = 0;
                q.push(vp);
                visited.insert(vp);
            }
            while(!q.empty()) {
                string node = q.front(); q.pop();
                int d = villager_distance[node];
                for(const auto& neighbor : connection[node]) {
                    if(!visited.count(neighbor)) {
                        villager_distance[neighbor] = d + 1;
                        visited.insert(neighbor);
                        q.push(neighbor);
                    }
                }
            }
        }
    }

    auto dist_other_hero = bfs_distance(other_hero_location);

    queue<pair<string,int>> q;
    unordered_map<string,string> parent;
    unordered_set<string> visited;
    q.push({current_hero_location, 0});
    visited.insert(current_hero_location);

    struct Candidate {
        string place;
        int dist_first_monster;
        int dist_second_monster;
        int villager_dist;
        int dist_other_hero;
    };
    vector<Candidate> candidates;

    while(!q.empty()){
        auto [node, step] = q.front(); q.pop();

        int d1 = dist_first_monster.count(node) ? dist_first_monster[node] : INT_MAX;
        int d2 = dist_second_monster.count(node) ? dist_second_monster[node] : INT_MAX;

        int current_d1 = dist_first_monster.count(current_hero_location) ? dist_first_monster[current_hero_location] : INT_MAX;
        int current_d2 = dist_second_monster.count(current_hero_location) ? dist_second_monster[current_hero_location] : INT_MAX;

        bool is_further_or_equal = (d1 >= current_d1) && (d2 >= current_d2);

        if(is_further_or_equal){
            
            int v_dist = villager_distance.count(node) ? villager_distance[node] : INT_MAX;
            int d_other_hero = dist_other_hero.count(node) ? dist_other_hero[node] : INT_MAX;

            candidates.push_back({node, d1, d2, v_dist, d_other_hero});
        }
        if(step == max_steps) continue;

        for(const auto& neighbor : connection[node]){
            if(!visited.count(neighbor)){

                visited.insert(neighbor);
                parent[neighbor] = node;
                q.push({neighbor, step + 1});
            }
        }
    }

    if(candidates.empty()){

        if(max_steps == 2) {
            return Move_Hero_Away_From_Monsters(current_hero_location, first_monster_location, second_monster_location, other_hero_location, 1);
        }
        return current_hero_location;
    }
    sort(candidates.begin(), candidates.end(), [](const Candidate& a, const Candidate& b){

        int min_dist_a = min(a.dist_first_monster, a.dist_second_monster);
        int min_dist_b = min(b.dist_first_monster, b.dist_second_monster);

        if(min_dist_a != min_dist_b) return min_dist_a > min_dist_b;

        if(a.villager_dist != b.villager_dist) return a.villager_dist < b.villager_dist;

        return a.dist_other_hero > b.dist_other_hero;
    });

    string best_place = candidates[0].place;

    vector<string> path;
    string current = best_place;

    while(current != current_hero_location) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());

    if((int)path.size() <= max_steps && !path.empty())
        return path.back();

    else if(path.empty())
        return current_hero_location;

    else
        return path[max_steps - 1];
}