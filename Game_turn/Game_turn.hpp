#ifndef GAME_TURN_HPP
#define GAME_TURN_HPP

#include "Game.hpp"

class Game_turn {

    public :

        virtual ~Game_turn() = default ;
        virtual bool phase(Game& gamestage) = 0 ;
        virtual void handle_turn(Game& gamestage) = 0 ;

    private :

};

#endif //GAME_TURN_HPP