#ifndef ADVANCE_H
#define ADVANCE_H

#include "../Hero_Action.hpp"
#include <string>


class Advance: public Hero_Action{

    public:

        bool Activate(Game&, Hero*);
        std::string info()const;
};

#endif//ADVANCE_H