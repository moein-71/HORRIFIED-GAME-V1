#include "Hero.hpp"
#include <iostream>
#include <sstream>
#include <random>
#include <variant>
#include <iomanip>

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

    if(item.empty()){
        cout << "Your item bag is empty.\n";
        return {};
    }

    unordered_map<Item, int> second_item;
    for(auto item_info: item){
        if(item_info.first.get_color() == color){
            second_item[item_info.first] = item_info.second;
        }
    }

    if(second_item.empty()){
        cout << "Your item bag whith " << color << " is empty.\n";
        return {};
    }

    for(auto item_name: second_item){
        cout << "Item name:" << item_name.first.get_name() << setw(5)
        << "Item number:" << item_name.second << '\n';
    }
    cout << "\n__________________________________________________________________________\n";

    bool Hozoor = 0;
    int sum_strength{};
    string choose_item;
    vector <Item> choose;
    unordered_map <Item, int> copy_item = second_item;
    while(1 && !copy_item.empty()){

        Hozoor = 0;

        cout << "Please enter name of item that you want or write exit.\n";
        getline(cin, choose_item);

        if(choose_item == "exit"){
            return {};
        }

        for(auto item_info: copy_item){
            if(item_info.first.get_name() == choose_item){
                
                Hozoor = 1;
                sum_strength += item_info.first.get_strength();
                choose.push_back(item_info.first);
                remove_item_from_bag(copy_item, item_info.first);
            }
        }
        if(!Hozoor){
            cout << "There is no such item.\n";
            continue;
        }
        if(sum_strength >= strength){
            break;
        }
    }
    if(sum_strength < strength){
        cout << "You can't run this action.\n";
        return {};
    }
    else{
        for(auto item_info: choose){
            remove_item_from_bag(item, item_info);
        }
        return choose;
    }
}
void Hero::remove_item_from_bag(unordered_map <Item, int>& bag_item, Item item){

    if(!(--bag_item[item])){
        bag_item.erase(item);
    }
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
variant<int, Item> Hero::When_Monster_Killed_A_Hero(){

    if(item.empty()){
       Go_To_Hospital();
       return 1;
    }
       
    int choose;
    string exeption_choose;

    while(1){

        cout << "Please enter number 1 if you want go to hospital, or number 2 for use an item and bach to life.\n";
        getline(cin, exeption_choose);
        istringstream iss(exeption_choose);

        if(iss >> choose){

            if(choose == 1){
                Go_To_Hospital();
                return 1;
            }
            
            else if(choose == 2){
                auto it = Back_To_Life_By_Use_An_Item();
                return it;
            }

            else{
                cerr << "Please enter number 1 or 2.\n";
            }
        }
        else{
            cerr << "Please enter the right value.\n";
        }
    }
}
Item Hero::Back_To_Life_By_Use_An_Item(){

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, item.size() - 1);

    int rand_index = dist(gen);
    auto it = item.begin();
    advance(it, rand_index);

    item[it->first]--;

    if(!item[it->first])
        item.erase(it->first);
    
    return it -> first;
}
void Hero::Go_To_Hospital(){
    set_now_place("Hospital");
}
string repeat(const string& s, int n) {
    string result;
    for (int i = 0; i < n; ++i)
        result += s;
    return result;
}
void Hero::Print_Hero_Info(){

    int name_width = 20;
    int color_width = 10;
    int loc_width = 18;
    int count_width = 7;
    int table_width = name_width + color_width + loc_width + count_width + 3;

    cout << "╔" << repeat("═", table_width) << "╗\n";
    cout << "║ Hero: " << left << setw(table_width - 7) << name << "║\n";
    cout << "║ Player: " << left << setw(table_width - 9) << player_name << "║\n";
    cout << "╠" << repeat("═", name_width) << "╦"
            << repeat("═", color_width) << "╦"
            << repeat("═", loc_width) << "╦"
            << repeat("═", count_width) << "╣\n";

    cout << "║ " << left << setw(name_width - 1) << "Item Name"
            << "║ " << left << setw(color_width - 1) << "Color"
            << "║ " << left << setw(loc_width - 1) << "Location"
            << "║ " << left << setw(count_width - 1) << "Count"
            << "║\n";

    cout << "╠" << repeat("═", name_width) << "╬"
            << repeat("═", color_width) << "╬"
            << repeat("═", loc_width) << "╬"
            << repeat("═", count_width) << "╣\n";

    for (const auto& [item_obj, count] : item) {
        string item_name = item_obj.get_name();
        if (item_name.length() > size_t(name_width - 2))
            item_name = item_name.substr(0, name_width - 5) + "...";

        string spawn = item_obj.get_spawn_place();
        if (spawn.length() > size_t(loc_width - 2))
            spawn = spawn.substr(0, loc_width - 5) + "...";

        cout << "║ " << left << setw(name_width - 1) << item_name
                << "║ " << left << setw(color_width - 1) << item_obj.get_color()
                << "║ " << left << setw(loc_width - 1) << spawn
                << "║ " << left << setw(count_width - 1) << count
                << "║\n";
    }

    cout << "╚" << repeat("═", name_width) << "╩"
            << repeat("═", color_width) << "╩"
            << repeat("═", loc_width) << "╩"
            << repeat("═", count_width) << "╝\n";
}