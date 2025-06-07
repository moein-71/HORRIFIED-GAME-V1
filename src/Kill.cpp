#include "Kill.hpp"

using namespace std ;

bool Kill::activate(Game & game , const std::string & monster) {

    return game.Game_map.kill_villager(game.invisible_man.get_now_place()) ;
}   
std::string Kill::info() const {}