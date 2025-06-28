#ifndef SPECIAL_ACTION_H
#define SPECIAL_ACTION_H

#include "../Hero_Action.hpp"
#include <unordered_map>
#include <string>


class Special_Action: public Hero_Action{

    public:

        void Activate(Game&, Hero*)override ;
        std::string info()const override;
};

#endif//SPECIAL_ACTION_H