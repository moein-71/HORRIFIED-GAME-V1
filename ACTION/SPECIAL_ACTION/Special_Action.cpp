#include "Special_Action.hpp"
#include <bits/stdc++.h>

using namespace std;

bool Special_Action::Activate(Game& game, Hero* hero){

    auto neighbor = game.Game_map.get_connection(game.archaologist.get_now_place());

    for(auto name_neighbor_place: neighbor){

        cout << "Place name:" << name_neighbor_place << '\n';

        for(auto item_info: game.Game_map.get_item_of_place(name_neighbor_place)){
                cout << "Item name:" << item_info.first.get_name() << setw(10) 
                << "Number item:" << item_info.second << '\n';
        }
        cout << "____________________________________________________________________\n";
    }

    string choose;
    cout << "If you want to stop special_action write exit.\n";

    int counter = 0 ;
    while(1){
        counter++ ;
        cout << "Please enter a place_name or write exit:\n";
        getline(cin, choose);

        if(choose == "exit") {
            if(counter == 1) {
                return false ;
            }
            return true ;
        }
        
        if(game.Game_map.Check_Count_Neighbor_Connection(game.archaologist.get_now_place() , choose)){

            auto it = game.Game_map.get_item_of_place(game.archaologist.get_now_place());
            game.Game_map.Remove_All_Item_In_Place(choose);

            for(auto pair_it: it){
                for(int i{pair_it.second}; i > 0; --i){
                    game.archaologist.set_item(pair_it.first);
                }
            }
        }
        else{
            cout << "Please enter the right name.\n";
        }
    }
}
std::string Special_Action::info()const{


}