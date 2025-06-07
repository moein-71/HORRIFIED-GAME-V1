#ifndef MONSTER_CARD_HPP
#define MONSTER_CARD_HPP

#include "Game.hpp"
#include "Monster_Action.hpp"

class Monster_card {

    public :

        virtual ~Monster_card() = default ;
        virtual void ability(Game& gamestage) = 0 ;
        virtual std::string info() const = 0 ;

    private :
};

#endif //MONSTER_CARD_HPP