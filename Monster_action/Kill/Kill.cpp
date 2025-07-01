#include "Kill.hpp"

using namespace std ;

bool Kill::activate(Game & game , const std::string & monster) {


    if(monster == game.dracula.get_name()) {
        if(game.get_dracula_place() == game.get_archaologist_place()) {
            game.archaologist.When_Monster_Killed_A_Hero() ;
            game.printLineDelay(game.get_dracula_name() + " Kill the archaologist\n") ;
            return true ;
        }
        else if(game.get_dracula_place() == game.get_mayor_place()) {
            game.mayor.When_Monster_Killed_A_Hero() ;
            game.printLineDelay(game.get_dracula_name() + " Kill the mayor\n") ;
            return true ;
        }
        return game.Game_map.Kill_Villager(game.dracula.get_now_place()) ;
        game.printLineDelay(game.get_dracula_name() + " Kill a villager in the night\n") ;
    }
    else if(monster == game.invisible_man.get_name()) {
        for(auto kill_villager : game.Game_map.get_villager(game.invisible_man.get_now_place())) {
            if(game.invisible_man.can_kill_villager(kill_villager)) {
                if(game.Game_map.Kill_Villager(game.invisible_man.get_now_place() , kill_villager.get_name())) {
                    game.printLineDelay(game.get_invisible_man_name() + " Kill a villager in the day\n") ;
                    return true ;
                }
            }
        }
    }

    // throw runtime_error("somthing goes wrong in Kill") ;    
    game.printLineDelay("Kill of " + monster + " is not successful\n") ;
    return false ;
}   
std::string Kill::info() const {

}