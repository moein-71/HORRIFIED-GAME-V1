#include "Move_monster.hpp"

using namespace std ;

bool Move_monster::activate(Game & game , int move , const string & monster) {

    if(monster == "dracula") {
            game.dracula.set_now_place(game.Game_map.find_destination(move , game.dracula.get_now_place() , game.mayor.get_now_place() , game.archaeologist.get_now_place())) ;
    }
    else if(monster == "invisible_man") {
            game.invisible_man.set_now_place(game.Game_map.find_destination(move , game.invisible_man.get_now_place() , game.mayor.get_now_place() , game.archaeologist.get_now_place())) ;
    }
}

std::string Move_monster::info() const {

} 