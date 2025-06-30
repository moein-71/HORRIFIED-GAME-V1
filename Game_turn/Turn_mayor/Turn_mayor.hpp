#ifndef TURN_MAYOR_HPP
#define TURN_MAYOR_HPP

#include "Game_turn.hpp"
#include "Break_of_Dawn.hpp"
#include "Hurry.hpp"
#include "Late_into_the_Night.hpp"
#include "Overstock.hpp"
#include "Repel.hpp"
#include "Visit_from_the_Detective.hpp"

class Turn_mayor : public Game_turn {

    public :

        bool phase(Game& gamestage) override ;
        void handle_turn(Game& gamestage) override ;

    private :
};

#endif //TURN_MAYOR_HPP