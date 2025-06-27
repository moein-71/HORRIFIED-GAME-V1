#include "Hurry.hpp"

using namespace std ;

void Hurry::ability(Game& gamestage) {

    const int move_hero = 2 ;

    gamestage.set_archaeologist_place(gamestage.find_far_destination_hero_map(move_hero , gamestage.get_archaeologist_place() , gamestage.get_dracula_place() , gamestage.get_invisible_man_place())) ;

    gamestage.set_mayor_place(gamestage.find_far_destination_hero_map(move_hero , gamestage.get_mayor_place() , gamestage.get_dracula_place() , gamestage.get_invisible_man_place())) ;
}

std::string Hurry::info() const {

    cout<< "move Heros two block far away from Monsters  \n" ;
}
