#include "Turn_monster.hpp"
#include "Egyptian_Expert.hpp"
#include "Former_Employer.hpp"
#include "Form_of_The_Bat.hpp"
#include "Fortune_Teller.hpp"
#include "Hurried_Assistant.hpp"
#include "Sunrise.hpp"
#include "The_Delivery.hpp"
#include "The_Ichthyologist.hpp"
#include "The_Innocent.hpp"
#include "Thief.hpp"

using namespace std ;

bool Turn_monster::phase(Game& gamestage) {

    shared_ptr<Monster_card> monster_phase = gamestage.get_random_monster_card() ;

    monster_phase->info() ;

    monster_phase->ability() ;
}