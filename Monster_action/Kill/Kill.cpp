#include "Kill.hpp"

using namespace std ;

bool Kill::activate(Game & game , const std::string & monster) {


    if(monster == game.dracula.get_name()) {
        if(game.get_dracula_place() == game.get_archaologist_place()) {
            game.archaologist.When_Monster_Killed_A_Hero() ;
            return true ;
        }
        else if(game.get_dracula_place() == game.get_mayor_place()) {
            game.mayor.When_Monster_Killed_A_Hero() ;
            return true ;
        }
        return game.Game_map.Kill_Villager(game.dracula.get_now_place()) ;
    }
    else if(monster == game.invisible_man.get_name()) {
        for(auto kill_villager : game.Game_map.get_villager(game.invisible_man.get_now_place())) {
            if(game.invisible_man.can_kill_villager(kill_villager)) {
                return game.Game_map.Kill_Villager(game.invisible_man.get_now_place() , kill_villager.get_name()) ;
            }
        }
    }

    throw runtime_error("somthing goes wrong in Kill") ;    
    return false ;
}   
std::string Kill::info() const {

}