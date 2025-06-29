#include "Power.hpp"

using namespace std ;

bool Power::activate(Game & game , const std::string & monster) {

    if(monster == game.dracula.get_name()) {
            game.get_last_hero_turn() == game.mayor.get_name() ? game.set_mayor_place(game.get_dracula_place()) : game.set_archaologist_place(game.get_dracula_place()) ;
            return true ;
    }
    else if(monster == game.invisible_man.get_name()) {
            game.invisible_man.set_now_place(game.Game_map.find_destination(2 , game.invisible_man.get_now_place() , "none" , "none")) ;
            return true ;
    }

    throw runtime_error("somthing goes wrong in Power") ;    
    return false ;
}

std::string Power::info() const {

}  
