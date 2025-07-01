#ifndef HURRIED_ASSISTANT_HPP
#define HURRIED_ASSISTANT_HPP

#include "Monster_card.hpp"

class Hurried_assistant : public Monster_card {

    public :

        void ability(Game& gamestage) override ;
        void info() const override ;

    private :
};

#endif //HURRIED_ASSISTANT_HPP