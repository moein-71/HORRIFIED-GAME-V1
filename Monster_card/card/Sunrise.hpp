#ifndef SUNRiSE_HPP
#define SUNRiSE_HPP

#include "Monster_card.hpp"

class Sunrise : public Monster_card {

    public :

        void ability(Game& gamestage) override ;
        void info() const override ;

    private :
};

#endif //SUNRiSE_HPP