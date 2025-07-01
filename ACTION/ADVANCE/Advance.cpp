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
                game.printLineDelay( item.get_name() + " added in invisible_man map in " + item.get_spawn_place() + '\n') ; 
                hero -> remove_item_from_bag(item) ;
                found = true ;
            }
        }
        
        if(found) {
            return true ;
        }
        game.printLineDelay("There is no new investigate item\n") ;
        return false ;
        
    }
    else if(casket.count(now_place)){

        bool destroyed = game.dracula.Check_Casket_Destroyed_In_Place(now_place);

        if(destroyed){
            game.printLineDelay("This casket destroied before you can't use this action\n");
            return false ;
        }

        vector<Item> item_info = hero -> get_item("Red", 6);

        if(item_info.empty()){
            game.printLineDelay( "You can't run this action because amount of your item are'nt enough.\n");
            return false ;
        }
        else {
            game.dracula.Destroy_Casket(now_place) ;
            game.printLineDelay( "Casket destroyed\n") ;
            return true ;
        }
    }
    else{
        cerr << "You cant use advance in this location.\n\n";
        return false ;
    }
}

std::string Advance::info()const {

}