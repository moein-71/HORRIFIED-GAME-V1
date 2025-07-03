#include "Special_Action.hpp"
#include <bits/stdc++.h>

using namespace std;

bool Special_Action::Activate(Game& game, Hero* hero){

    auto neighbor = game.Game_map.get_connection(game.archaologist.get_now_place());

    for(auto name_neighbor_place: neighbor){

        game.printLineDelay( "Place name:" + name_neighbor_place + '\n');

        for(auto item_info: game.Game_map.get_item_of_place(name_neighbor_place)){
                game.printLineDelay( "Item name:" + item_info.first.get_name() + "  " + "Number item:" + to_string(item_info.second) + '\n' );
        }
        game.printLineDelay( "____________________________________________________________________\n");
    }

    string choose;

    int counter = 0 ;
    while(1){
        counter++ ;
        game.printLineDelay( "Please enter a place_name or write exit for exit :\n");
        cin>> choose ;

        if(choose == "exit") {
            return false ;
        }
        
        if(game.Game_map.Check_Count_Neighbor_Connection(game.archaologist.get_now_place() , choose)){

            auto it = game.Game_map.get_item_of_place(choose);
            game.Game_map.Remove_All_Item_In_Place(choose);

            for(auto pair_it: it){
                for(int i{}; i < pair_it.second; ++i){
                    game.archaologist.set_item(pair_it.first);
                    
                }
            }
            cout<< "Kjkajdf" ;
            return true ;
        }
        else{
            game.printLineDelay( "Please enter the right name.\n");
        }
    }
}
std::string Special_Action::info()const{
    return "SPECIAL_ACTION : Archaologist can get how many item he want from Neighbor places\n" ;
}