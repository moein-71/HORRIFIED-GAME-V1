#include "Advance.hpp"
#include <bits/stdc++.h>

using namespace std;

bool Advance::Activate(Game& game, Hero* hero){

    string now_place = hero -> get_now_place();
    auto casket = game.dracula.get_casket();

    if(now_place == "Precinct"){

        vector<Item> investigate_item = hero -> get_investigate_item() ;

        bool found = false ;
        for(auto item: investigate_item){
            if(game.invisible_man.set_investigate_found(item.get_spawn_place())) {
                cout<< item.get_name() << " added in invisible_man map in " << item.get_spawn_place() << '\n' ; 
                hero -> remove_item_from_bag(item) ;
                found = true ;
            }
        }
        
        if(found) {
            return true ;
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

std::string Advance::info()const {

}