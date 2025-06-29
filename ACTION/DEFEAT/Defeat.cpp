#include "Defeat.hpp"
#include <bits/stdc++.h>

using namespace std;

bool Defeat::Activate(Game& game, Hero* hero) {
    if(hero->get_now_place() == game.get_dracula_place()) {
        if(game.dracula.Check_Casket()) {
            vector<Item> defeat_item = hero->get_item("Yellow" , 6) ;

            if(!defeat_item.empty()) {
                game.set_dracula_place("DEAD") ;
                cout<< "Dracula died\n" ;
            }
            else {
                cout<< "You cant defeat dracula\n" ;
            }
        }
        else {
            cout<< "All of the Caskets are not destroyed\n" ;
        }
    }
    else if(hero->get_now_place() == game.get_invisible_man_place()) {
        if(game.invisible_man.check_investigate()) {
             vector<Item> defeat_item = hero->get_item("Red" , 9) ;

            if(!defeat_item.empty()) {
                game.set_invisible_man_place("DEAD") ;
                cout<< "Invisible_man died\n" ;
            }
            else {
                cout<< "You cant defeat invisible_man\n" ;
            }
        }
        else {
            cout<< "All of the investigates are not found\n" ;
        }
    }
    else {
        cout<< "You are not in the monster place\n" ;
    }
}

std::string Defeat::info()const {

}