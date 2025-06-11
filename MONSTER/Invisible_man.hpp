#ifndef INVISIBLE_MAN_H
#define INVISIBLE_MAN_H

#include "Monster.hpp"
#include "../VILLAGER/Villager.hpp"
#include <unordered_map>
#include <vector>
#include <string>

class Invisible_man: public Monster{

    public:

        Invisible_man();

        void reset_near_villager(std:: vector<Villager>);
        bool set_investigate_found(std::string);
        bool can_kill_villager(Villager);

    private:

        std::unordered_map <std::string, bool> investigate;
        std::unordered_map <Villager, bool> near_villager;
};

#endif//INVISIBLE_MAN_H