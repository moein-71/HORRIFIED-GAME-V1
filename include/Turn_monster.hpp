#ifndef TURN_MONSTER_HPP
#define TURN_MONSTER_HPP

#include "Game_turn.hpp"
#include "Egyptian_Expert.hpp"
#include "Former_Employer.hpp"
#include "Form_of_The_Bat.hpp"
#include "Fortune_Teller.hpp"
#include "Hurried_Assistant.hpp"
#include "Sunrise.hpp"
#include "The_Delivery.hpp"
#include "The_Ichthyologist.hpp"
#include "The_Innocent.hpp"
#include "Thief.hpp"

class Turn_monster : public Game_turn {

    public :

        bool phase(Game& gamestage) override ;

    private :
};

#endif //TURN_MONSTER_HPP