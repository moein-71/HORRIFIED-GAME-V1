#ifndef PERK_CARD_HPP
#define PERK_CARD_HPP

#include "Game.hpp"
// #include ".hpp" // hero action

class Perk_card {

    public :

        virtual ~Perk_card() = default ;
        virtual void ability(Game& gamestage) = 0 ;
        virtual std::string info() const = 0 ;

    private :
};

#endif //PERK_CARD_HPP