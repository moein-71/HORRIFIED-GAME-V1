#include "Advance.hpp"
#include <bits/stdc++.h>

using namespace std;

bool Advance::Activate(Game& game, Hero* hero){

    string now_place = hero -> get_now_place();
    auto casket = game.dracula.get_casket();

    if(now_place == "Precinct"){

        unordered_map<string, Item> founded_items = hero -> get_investigate_item();

        for(auto item: founded_items){
            if(game.invisible_man.set_investigate_found(item.second.get_spawn_place())) {
                cout<< "Investigate item added\n" ; 
                return true ;
            }
        }
        cout<< "There is no new investigate item\n" ;
        return false ;
        
    }
    else if(casket.count(now_place)){

        bool destroyed = game.dracula.Check_Casket_Destroyed_In_Place(now_place);

        if(!destroyed){
            cout << "This casket destroied before you can't use this action\n";
            return false ;
        }

        vector<Item> item_info = hero -> get_item("Red", 6);

        if(item_info.empty()){
            cout << "You can't run this action because amount of your item are'nt enough.\n";
            return false ;
        }
        else {
            game.dracula.Destroy_Casket(now_place) ;
            cout<< "Casket destroyed\n" ;
            return true ;
        }
    }
    else{
        cerr << "You are in a location where you cannot use this action.\n";
        return false ;
    }
}