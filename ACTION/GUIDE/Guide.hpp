#ifndef GUIDE_H
#define GUIDE_H

#include "../Hero_Action.hpp"
#include <string>
#include <vector>


class Guide: public Hero_Action{

    public:

        bool Activate(Game&, Hero*);
        std::string info()const;

        std::string send_villager_another_place(std::string, std::string, std::string, std::vector<std::string>, Game& , Hero*);
        std::string take_villager_another_place(std::string, std::string, std::string, std::vector<std::string>, Game& , Hero*);
};

#endif//GUIDE_H