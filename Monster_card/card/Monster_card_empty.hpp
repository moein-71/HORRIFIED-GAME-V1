#ifndef MONSTER_CARD_EMPTY_HPP
#define MONSTER_CARD_EMPTY_HPP

#include "Monster_card.hpp"

class Monster_card_empty : public Monster_card {

    public :

        void ability(Game& gamestage) override ;
        void info() const override ;

    private :
};

#endif //MONSTER_CARD_EMPTY_HPP