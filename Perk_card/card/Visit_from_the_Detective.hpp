#ifndef VISIT_FROM_THE_DETECTIVE_HPP
#define VISIT_FROM_THE_DETECTIVE_HPP

#include "Perk_card.hpp"

class Visit_from_the_detective : public Perk_card {

    public :

        void ability(Game& gamestage) override ;
        std::string info() const override ;

    private :
};

#endif //VISIT_FROM_THE_DETECTIVE_HPP