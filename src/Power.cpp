#include "Power.hpp"

using namespace std ;

bool Power::activate(Game & game , const std::string & monster) {
    game.invisible_man.set_now_place(game.Game_map.find_destination(2 , game.invisible_man.get_now_place() , "none" , "none")) ;
    return true ;
}

std::string Power::info() const {

}  
