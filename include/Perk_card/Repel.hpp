#ifndef REPEL_HPP
#define REPEL_HPP

#include "Perk_card.hpp"

class Repel : public Perk_card {

    public :

        void ability(Game& gamestage) override ;
        std::string info() const override ;

    private :
};

#endif //REPEL_HPP