#include "Move_Hero.hpp"
#include <bits/stdc++.h>

using namespace std;

bool Move_Hero::Activate(Game& game, Hero* hero){

    string now_place = hero -> get_now_place();
    auto neighbor = game.Game_map.get_connection(now_place);

    cout << "Your neighbor of now_place are:\n";
    for(auto neighbor_place_name: neighbor){
        cout << neighbor_place_name << setw(5); 
    }
    cout << '\n';

    bool Hozoor{};
    bool found{0};
    string choose_place_name;
    while(!found){

        Hozoor = 0;

        cout << "Please enter the name of place that you want to go there or you want to stop move_hero then write exit.\n";
        getline(cin, choose_place_name);
        
        if(choose_place_name == "exit")
            return false ;
            break;

        for(auto neighbor_place_name: neighbor){
            
            if(neighbor_place_name == choose_place_name){

                Hozoor = 1;

                vector<Villager> villager = game.Game_map.get_villager(now_place);

                if(villager.empty()){

                    hero -> set_now_place(choose_place_name);
                    return true ;
                }
                
                for(int i{}; i < villager.size(); ++i){
                    cout << "Villager name: " << villager[i].get_name() << '\n';
                }
                cout << "___________________________________________________________________\n";

                hero -> set_now_place(choose_place_name);

                while(1){

                    cout << "Please enter villager's name that you want or write exit.\n";
                    string villager_name;
                    getline(cin, villager_name);

                    if(villager_name == "exit"){
                        found = 1;
                        return true ;
                    }

                    if(!(game.Game_map.set_villager_place(now_place, choose_place_name, villager_name))){
                        cout << "Please enter the right name.\n";
                    }
                    else {
                        if(choose_place_name == game.Game_map.get_villager_safe_place(choose_place_name , villager_name)) {
                            hero->set_perk(game.get_random_perk()) ;
                        }   
                    }
                }
            }
        }
        if(!Hozoor){
            cerr << "There is no place with this name.\n";
        }
        
    }

}

std::string Move_Hero::info()const {

}