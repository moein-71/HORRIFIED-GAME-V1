#ifndef DEFEAT_H
#define DEFEAT_H

#include "../Hero_Action.hpp"
#include <string>


class Defeat: public Hero_Action{

    public:

        void Activate(Game&, Hero*);
        std::string info()const;
};

#endif//DEFEAT_H