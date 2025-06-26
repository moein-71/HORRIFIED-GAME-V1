#ifndef TURN_MONSTER_HPP
#define TURN_MONSTER_HPP

#include "Game_turn.hpp"
// #include ".hpp" // hero action

class Turn_monster {

    public :

        virtual bool phase(Game& gamestage) = 0 ;

    private :
};

#endif //TURN_MONSTER_HPP