#ifndef MOVE_MONSTER_HPP
#define MOVE_MONSTER_HPP

#include "Monster_Action.hpp"

class Move_monster : public Monster_action {

    public :

        bool activate(Game & game , int move , const string & monster) override ;   
        std::string info() const override ;  

    private :

} ;

#endif //MOVE_MONSTER_HPP
