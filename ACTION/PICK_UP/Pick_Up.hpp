#ifndef PICK_UP_H
#define PICK_UP_H

#include "../Hero_Action.hpp"
#include <string>


class Pick_Up: public Hero_Action{

    public:

        void Activate(Game&, Hero*) override;
        std::string info()const override;
};

#endif//PICK_UP_H