#ifndef HERO_H
#define HERO_H

#include "../ITEM/Item.hpp"
#include <string>
#include <unordered_map>
#include <memory>

////////////////////////////////////////////////(   TEMP_ CLASS   )////////////////////////////////////////////////////////////
class Perk{

    public:
        Perk() = default;
};
////////////////////////////////////////////////(   TEMP_ CLASS   )////////////////////////////////////////////////////////////

class Hero{

    public:

        Hero() = default;
        Hero(std::string, std:: string, bool, int);

        void set_special_action_info(bool);
        void set_name(std::string);
        void set_player_name(std::string);
        void set_spawn_place(std::string);
        void set_now_place(std::string);

        bool get_special_action_info()const;
        int get_action()const;
        std::string get_name()const;
        std::string get_player_name()const;
        std::string get_spawn_place()const;
        std::string get_now_place()const;

        void Describe_Hero_Special_Action();// this function describe the special action of all hero
        
    private:
\
        bool special_action_info;
        const int action;
        std::string name;
        std:: string player_name;
        std::string spawn_place;
        std::string now_place;


        unordered_map <std::shared_ptr<Perk>, int> perk;
        unordered_map <Item, int> item;
        unordered_map <std::string, Item> investigate_item;
};

#endif//HERO_H