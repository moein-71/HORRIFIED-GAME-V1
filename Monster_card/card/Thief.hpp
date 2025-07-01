#ifndef THIEF_HPP
#define THIEF_HPP

#include "Monster_card.hpp"

class Thief : public Monster_card {

    public :

        void ability(Game& gamestage) override ;
        void info() const override ;

    private :
};

#endif //THIEF_HPP