#ifndef HERO_ACTION_H
#define HERO_ACTION_H

#include <string>


class Hero_Action{

    public:

        virtual ~Hero_Action() = default;

        virtual bool Activate(Game&, Hero*) = 0;
        virtual std::string info()const = 0;
};

#endif//HERO_ACTION_H