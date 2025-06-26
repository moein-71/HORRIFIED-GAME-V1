#ifndef POWER_HPP
#define POWER_HPP

#include "Monster_action.hpp"

class Power : public Monster_action {

    public :

        bool activate(Game & game , const std::string & monster) override ;   
        std::string info() const override ;  

    private :

} ;

#endif //POWER_HPP