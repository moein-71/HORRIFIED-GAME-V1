#ifndef THE_INNOCENT_HPP
#define THE_INNOCENT_HPP

#include "Monster_card.hpp"

class The_innocent : public Monster_card {

    public :

        void ability(Game& gamestage) override ;
        void info() const override ;

    private :
};

#endif //THE_INNOCENT_HPP