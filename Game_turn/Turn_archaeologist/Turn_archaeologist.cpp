#include "Turn_archaeologist.hpp"
#include "Turn_monster.hpp"

using namespace std ;

bool Turn_archaeologist::phase(Game& gamestage) {
    
}

void Turn_archaeologist::handle_turn(Game& gamestage) {

    gamestage.turn = gamestage.monster ;
}