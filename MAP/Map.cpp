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
#include <iomanip>

using namespace std;

Map::Map(){

    set_connection();
}
vector<Villager> Map::get_villager(string place){
    return villager_place[place];
}
std::string Map::get_villager_place(std::string name) {
    for(auto vec_villager : villager_place) {
        for(auto villager : vec_villager.second) {
            if(villager.get_name() == name) {
                return vec_villager.first ;
            }
        }
    }
    cout<< "this villager not exist\n" ;
    return "" ;
}

std::string Map::get_villager_safe_place(std::string place , std::string name) {
    for(auto villager : villager_place[place]) {
        if(villager.get_name() == name) {
            return villager.get_safe_place() ;
        }
    }
    return "" ;
}

vector<string> Map::get_connection(std::string place){
    return connection[place] ;
}
std::unordered_map<Item, int> Map::get_item_of_place(std::string place){
    return item_place[place] ;
}
int Map::get_item_number(std::string place , std::string item_name) {
    for(const auto& pair : item_place[place]) {
        if(pair.first.get_name() == item_name) {
            return pair.second ;
        }
    }
    return 0 ;
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

bool Map::Check_Count_Item_Place(std::string place ,std::string item_name) {
    for(auto pair : item_place[place]) {
        if(pair.first.get_name() == item_name) {
            return true ;
        }
    }
    return false ;
}

bool Map::Check_Count_Neighbor_Connection(std::string now_place , std::string neighbor) {
    for(string place : connection[now_place]) {
        if(place == neighbor) {
            return true ;
        }
    }
    return false ;
}

bool Map::Check_Place_Exist(std::string place) {
    if(connection.count(place)) {
        return true ;
    }
    return false ;
}


bool Map::Kill_Villager(string place , string name){

    if(name != "") {
        if(villager_place[place].size() >= 1) {
            for(int i{} ; auto kill_villager : villager_place[place]) {
                if(kill_villager.get_name() == name) {
                    villager_place[place].erase(villager_place[place].begin() + i);
                    if(!villager_place[place].size()){
                        villager_place.erase(place);
                    }
                    return true ;
                }
                i++ ;
            }
            
        }
        return false ;
    }

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

    for(const auto& item: item_place[place]){
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
        for(const auto& item: place_name.second){
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
    for(const auto& item: item_place[place]){
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
    int max_steps)
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



////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////(           PRINT             )///////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
string trim(const string& str, size_t width){

    if(str.length() <= width) return str;
    if(width <= 3) return str.substr(0, width);
    return str.substr(0, width - 3) + "...";
}
string Map::repeat(const string& s, int n){

    string result;
    for(int i = 0; i < n; ++i){
        result += s;
    }
    return result;
}
void Map::Print_Map_And_All_Info
(
    string archaologist_place, 
    string mayor_place, 
    string dracula_place, 
    string invisible_mam_place,
    unordered_map<string, bool> casket,
    unordered_map<string, bool> investigate
){
cout << R"(
╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
║                                     The Cursed Land (Horrified)                                                  ║
╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════════╣
║  Cave ___Camp           Precinct        Inn                  Bank                Dungeon                         ║
║           |                 |            |                     |                    |                            ║
║           |                 |            |                     |                    |                            ║
║           |_________________|____________|__________________Theatre ______________Tower_____Docks                ║
║                  |                                            |                                                  ║
║                  |                                            |                                                  ║
║      Abbey_____Mansion______________________________________Shop________________Laboratory                       ║
║        |                               |             |                              |                            ║
║        |                               |             |                              |                            ║
║        |                               |             |                              |                            ║
║     Crypt                           Museum         Church                        Institute                       ║
║                                                     |                                                            ║
║                                                     |                                                            ║
║                                        Hospital_____|                                                            ║
║                                                     |                                                            ║
║                                                Graveyard                                                         ║
╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
)";

    const int table_width = 45;

    cout << "╔" << repeat("═", table_width) << "╗    ╔" << repeat("═", table_width) << "╗\n";
    cout << "║ " << setw(table_width - 2) << left << "Dracula Casket"
         << " ║    ║ " << setw(table_width - 2) << left << "Invisible Man Investigate Item" << " ║\n";
    cout << "╠" << repeat("═", table_width) << "╣    ╠" << repeat("═", table_width) << "╣\n";

    auto casket_ptr = casket.begin();
    auto investigate_ptr = investigate.begin();
    size_t max_rows = max(casket.size(), investigate.size());

    for(size_t i = 0; i < max_rows; ++i){
        string casket_line = " ";
        string investigate_line = " ";

        if(casket_ptr != casket.end()){
            string name = casket_ptr->first;
            string status = casket_ptr->second ? "Intact" : "Broken";
            casket_line = name + string(24 - name.size(), ' ') + ": " + status;
            ++casket_ptr;
        }

        if(investigate_ptr != investigate.end()){
            string name = investigate_ptr->first;
            string status = investigate_ptr->second ? "Found" : "Missing";
            investigate_line = name + string(24 - name.size(), ' ') + ": " + status;
            ++investigate_ptr;
        }

        cout << "║ " << setw(table_width - 2) << left << casket_line << " ║    ║ "
             << setw(table_width - 2) << left << investigate_line << " ║\n";
    }
    cout << "╚" << repeat("═", table_width) << "╝    ╚" << repeat("═", table_width) << "╝\n";

    Print_Character_Info(archaologist_place, mayor_place, dracula_place, invisible_mam_place);
}
void Map::Print_Character_Info
(
    string archaologist_place, 
    string mayor_place, 
    string dracula_place, 
    string invisible_mam_place
){

    const int left_width = 45;
    const int right_width = 55;
    const int space = 4;

    cout << "╔" << repeat("═", left_width) << "╗"
              << string(space, ' ')
              << "╔" << repeat("═", right_width) << "╗\n";

    cout << "║ " << left << setw(20) << "Villager"
              << " : " << setw(left_width - 24) << "Location"
              << "║" << string(space, ' ')
              << "║ " << left << setw(25) << "Item"
              << " : " << setw(right_width - 33) << "Location"
              << "(x) ║\n";

    cout << "╠" << repeat("═", left_width) << "╣"
              << string(space, ' ')
              << "╠" << repeat("═", right_width) << "╣\n";

    vector<pair<string, string>> villager_entries;
    for(const auto& [place, villagers]: villager_place){
        for(const auto& v: villagers){
            villager_entries.emplace_back(v.get_name(), place);
        }
    }

    vector<tuple<string, string, int>> item_entries;
    for(const auto& [place, items]: item_place){
        for(const auto& [item, count]: items){
            item_entries.emplace_back(item.get_name(), place, count);
        }
    }

    size_t maxLines = max(villager_entries.size(), item_entries.size());

    for(size_t i = 0; i < maxLines; ++i){
        if(i < villager_entries.size()){
            auto& [name, place] = villager_entries[i];
            cout << "║ " << left << setw(20) << name
                      << " : " << setw(left_width - 24) << place
                      << "║";
        } 
        else{
            cout << "║" << string(left_width, ' ') << "║";
        }

        cout << string(space, ' ');

        if(i < item_entries.size()){

            auto& [investigate_name, investigate_place, investigate_count] = item_entries[i];
            cout << "║ " << left << setw(25) << investigate_name
                      << " : " << setw(right_width - 33) << investigate_place
                      << "(" << investigate_count << ") ║";
        } 
        
        else{
            cout << "║" << string(right_width, ' ') << "║";
        }
        cout << '\n';
    }

    cout << "╚" << repeat("═", left_width) << "╝"
              << string(space, ' ')
              << "╚" << repeat("═", right_width) << "╝\n";

cout << R"(
                        ╔══════════════════════════════════════════════════╗
                        ║             Character Locations                  ║
                        ║══════════════════════════════════════════════════║
                        ║ Archaeologist  : )" << setw(20) << left << archaologist_place << R"(            ║

                        ║ Mayor          : )" << setw(20) << left << mayor_place << R"(            ║

                        ║ Dracula        : )" << setw(20) << left << dracula_place << R"(            ║

                        ║ Invisible_Man  : )" << setw(20) << left << invisible_mam_place << R"(            ║
                        ╚══════════════════════════════════════════════════╝
)" << '\n';
}