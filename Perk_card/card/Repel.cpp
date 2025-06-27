#include "Repel.hpp"

using namespace std ;

void Repel::ability(Game& gamestage)  {

    const int move_monster = 2 ;

    gamestage.set_dracula_place(gamestage.find_far_destination_monster_map(move_monster , gamestage.get_dracula_place() , gamestage.get_archaeologist_place() , gamestage.get_mayor_place())) ;

    gamestage.set_invisible_man_place(gamestage.find_far_destination_monster_map(move_monster , gamestage.get_invisible_man_place() , gamestage.get_archaeologist_place() , gamestage.get_mayor_place())) ;
}

std::string Repel::info() const  {

        cout<< "move Monsters two block far away from People  \n" ; 
}
