#ifndef HURRY_HPP
#define HURRY_HPP

#include "Perk_card.hpp"

class Hurry : public Perk_card {

    public :

        void ability(Game& gamestage) override ;
        std::string info() const override ;

    private :
};

#endif //HURRY_HPP