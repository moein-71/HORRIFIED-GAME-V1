#ifndef TURN_MONSTER_HPP
#define TURN_MONSTER_HPP

#include "Game_turn.hpp"
#include "Break_of_Dawn.hpp"
#include "Hurry.hpp"
#include "Late_into_the_Night.hpp"
#include "Overstock.hpp"
#include "Repel.hpp"
#include "Visit_from_the_Detective.hpp"

class Turn_archaeologist : public Game_turn {

    public :

        bool phase(Game& gamestage) override ;

    private :
};

#endif //TURN_MONSTER_HPP