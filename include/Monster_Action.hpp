#ifndef MONSTER_ACTION_HPP
#define MONSTER_ACTION_HPP

#include "Game.hpp"

class Monster_action {

    public :

        virtual ~Monster_action() = default ;
        virtual bool activate(Game & game , int move , const string & monster) = 0 ;  // pure 
        virtual std::string info() const = 0 ;  // pure 

    private :
} ;

#endif //MONSTER_ACTION_HPP
