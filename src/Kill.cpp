#include "Kill.hpp"

using namespace std ;

bool Kill::activate(Game & game , const std::string & monster) {


    if(monster == game.dracula.get_name()) {
        return game.Game_map.kill_villager(game.dracula.get_now_place()) ;
    }
    else if(monster == game.invisible_man.get_name()) {
        return game.Game_map.kill_villager(game.invisible_man.get_now_place()) ;
    }

    throw runtime_error("somthing goes wrong in Kill") ;    
    return false ;
}   
std::string Kill::info() const {

}