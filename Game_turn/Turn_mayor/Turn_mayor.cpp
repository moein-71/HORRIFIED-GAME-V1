#include "Turn_mayor.hpp"
#include "Turn_monster.hpp"

using namespace std ;

bool Turn_mayor::phase(Game& gamestage) {
    
}

void Turn_mayor::handle_turn(Game& gamestage) {

    gamestage.turn = gamestage.monster ;
}
