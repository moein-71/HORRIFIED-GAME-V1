#include "Move_monster.hpp"

using namespace std ;

bool Move_monster::activate(Game & game , const string & monster) {

    if(monster == "dracula") {
            game.dracula.set_now_place(game.Game_map.find_destination(1 , game.dracula.get_now_place() , game.mayor.get_now_place() , game.archaeologist.get_now_place())) ;
            return true ;
    }
    else if(monster == "invisible_man") {
            game.invisible_man.set_now_place(game.Game_map.find_destination(1 , game.invisible_man.get_now_place() , game.mayor.get_now_place() , game.archaeologist.get_now_place())) ;
            return true ;
    }

    throw runtime_error("somthing goes wrong in Move_monster") ;    
    return false ;
    
}

std::string Move_monster::info() const {

} 