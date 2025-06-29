#ifndef HERO_H
#define HERO_H

#include "../ITEM/Item.hpp"
#include <string>
#include <unordered_map>
#include <memory>
#include <variant>
#include "Perk_card.hpp"

class Hero{

    public:

        Hero() = default;
        Hero(std::string, std:: string, bool, int);

        void set_name(std::string);
        void set_player_name(std::string);
        void set_spawn_place(std::string);
        void set_now_place(std::string);
        void set_item(Item);
        void set_investigate_item();

        bool get_special_action_info()const;
        int get_action()const;
        std::string get_name()const;
        std::string get_player_name()const;
        std::string get_spawn_place()const;
        std::string get_now_place()const;
        shared_ptr<Perk_card> get_perk();
        vector <Item> get_item(std::string, int);
        void remove_item_from_bag(std::unordered_map <Item, int>&, Item);
        std::unordered_map <std::string, Item> get_investigate_item()const;

        void Describe_Hero_Special_Action();//this function describe the special action of all hero
        bool edit_investigate_item(Item);//if item has found this func return false 
        std::variant<int, Item> When_Monster_Killed_A_Hero();
        Item Back_To_Life_By_Use_An_Item();
        void Go_To_Hospital();
        
    private:

        const bool special_action_info;
        const int action;
        std::string name;
        std::string player_name;
        std::string spawn_place;
        std::string now_place;


        std::unordered_map <std::shared_ptr<Perk_card>, int> perk;
        std::unordered_map <Item, int> item;
        std::unordered_map <std::string, Item>static investigate_item;
};

#endif//HERO_H