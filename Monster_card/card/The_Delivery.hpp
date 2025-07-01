#ifndef THE_DELIVERY_HPP
#define THE_DELIVERY_HPP

#include "Monster_card.hpp"

class The_delivery : public Monster_card {

    public :

        void ability(Game& gamestage) override ;
        void info() const override ;

    private :
};

#endif //THE_DELIVERY_HPP