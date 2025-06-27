#ifndef BREAK_OF_DAWN_HPP
#define BREAK_OF_DAWN_HPP

#include "Perk_card.hpp"

class Break_of_dawn : public Perk_card {

    public :

        void ability(Game& gamestage) override ;
        std::string info() const override ;

    private :
};

#endif //BREAK_OF_DAWN_HPP