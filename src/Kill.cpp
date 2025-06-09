#include "Kill.hpp"

using namespace std ;

bool Kill::activate(Game & game , const std::string & monster) {


    if(monster == game.dracula.get_name()) {
        if(game.get_dracula_place() == game.get_archaeologist_place()) {
            if(!game.archaeologist.get_item()) {
                game.set_archaeologist_place("Hospital") ;
                return true ;
            }
            return true ;
        }
        else if(game.get_dracula_place() == game.get_mayor_place()) {
            if(!game.mayor.get_item()) {
                game.set_mayor_place("Hospital") ;
                return true ;
            }
            return true ;
        }
        return game.Game_map.kill_villager(game.dracula.get_now_place()) ;
    }
    else if(monster == game.invisible_man.get_name()) {
        return game.Game_map.kill_villager(game.invisible_man.get_now_place()) ; //we can't kill hero
    }

    throw runtime_error("somthing goes wrong in Kill") ;    
    return false ;
}   
std::string Kill::info() const {

}