#include "Hero.hpp"
#include <iostream>
#include <sstream>
#include <random>
#include <variant>
#include <iomanip>
#include "Perk_card.hpp"
#include "../ITEM/Item.hpp"

using namespace std;

Hero::Hero(string name, string spawn_and_now_place, bool special_action_info, int action): action(action), special_action_info(1) {

    set_name(name);
    set_spawn_place(spawn_and_now_place);
    set_now_place(spawn_and_now_place);
    investigate_place.push_back("Inn")  ;
    investigate_place.push_back("Barn")  ;
    investigate_place.push_back("Institute")  ;
    investigate_place.push_back("Laboratory")  ;
    investigate_place.push_back("Mansion") ;
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

void Hero::set_perk(shared_ptr<Perk_card> new_perk) {
    if(perk.count(new_perk)) {
        perk[new_perk]++ ;
        return ;
    }
    else {
        perk[new_perk] = 1 ;
    }
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
variant<std::shared_ptr<Perk_card> , bool> Hero::get_perk(){

    if(perk.empty()) {
        return false ;
    }

    int counter{1};
    vector <shared_ptr<Perk_card>> vec;

    for(auto print: perk){

        cout << counter << '.' << (*print.first).get_perk_name() << '   ';
        vec.push_back(print.first);
        counter++;
    }

    cout << counter << '.' << "exit \n";
    cout << "Whitch perk do you want : \n";
    int choose;
    string ch;cin >> ch;
    istringstream iss(ch);

    if(iss >> choose && choose >= 1 && choose <= counter){

        if(choose == counter){

            return nullptr;//if player want to exit in this time func retrunes nullptr
        }

        cout<< "INFO :\n" << vec[choose - 1]->info() << '\n' ;
        cout<< "\nIf you want to back type : N , otherwise only type a letter\n" ;
        string y_or_n ; 
        cin>> y_or_n ;
        if(y_or_n == "N") {
            return true ;
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
vector<Item> Hero::get_item(string color, int strength){

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
                remove_item_from_bag(item_info.first , &copy_item);
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
            remove_item_from_bag(item_info);
        }
        return choose;
    }
}

vector<Item> Hero::get_investigate_item() {
    vector<Item> temp ;
    for(auto pair : item) {
        for(auto place : investigate_place) {
            if(pair.first.get_spawn_place() == place) {
                temp.push_back(pair.first) ;
            }
        }
    }
    return temp ;
}

void Hero::remove_item_from_bag(Item remove_item , std::unordered_map <Item, int>* item_bag ){

    item_bag == nullptr ? item_bag = &(this -> item) : item_bag = item_bag ;
    if(!(--(*item_bag)[remove_item])){
        (*item_bag).erase(remove_item);
    }
}

void Hero::Describe_Hero_Special_Action(){

cout << R"(
Archaologist: 
He can pick up any number of items from a nearby location.

Mayor:
She Has no special action.

)";
}

variant<int, Item> Hero::When_Monster_Killed_A_Hero(){

    if(item.empty()){
       Go_To_Hospital();
       return 1;
    }
       
    int choose;
    string exeption_choose;
    cin.ignore() ;
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
                return Back_To_Life_By_Use_An_Item();
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

    auto it = item.begin() ;

    it->second-- ;

    auto temp = it->first ;

    if(it -> second == 0)
        item.erase(it);
    
    return temp;

}
void Hero::Go_To_Hospital(){
    set_now_place("Hospital");
}
string Hero::repeat(const string& s, int n) {
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
    cout << "║ Hero: " << left << setw(table_width - 7)
            << (name + " (" + now_place + ")") << "║\n";
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
    if(!item.empty()){
        for(const auto& [item_obj, count] : item){

            string item_name = item_obj.get_name();
            if(item_name.length() > size_t(name_width - 2))
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
        }

    cout << "╚" << repeat("═", name_width) << "╩"
            << repeat("═", color_width) << "╩"
            << repeat("═", loc_width) << "╩"
            << repeat("═", count_width) << "╝\n";
}