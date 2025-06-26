#include "Turn_monster.hpp"

using namespace std ;

bool Turn_monster::phase(Game& gamestage) {

    shared_ptr<Monster_card> monster_phase = gamestage.get_random_monster_card() ;

    monster_phase->info() ;

    monster_phase->ability() ;
}