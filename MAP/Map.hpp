#ifndef MAP_H
#define  MAP_H

#include "../VILLAGER/Villager.hpp"
#include "../ITEM/Item.hpp"
#include "../HERO/Mayor.hpp"
#include "../HERO/Archaologist.hpp"
#include <string>
#include <unordered_map>
#include <vector>

class Map{

    public:

        Map();
        vector<Villager> get_villager(std::string);

        void set_connection();
        void set_item(Item);
        void set_villager(std::string, Villager);//This function add Villager
        void set_villager_place(std::string, std::string);//This function edit villager_place

        bool Kill_Villager(std::string); 
        Item Pickeup_Item(std::string, std::string);
        std::string Find_Place_With_More_Item();
        std::vector<pair<Item, int>> Remove_All_Item_In_Place(std::string);
        //std::string Find_Destination(int, std::string, Archaologist, Mayor);

    private:

        std::unordered_map<std::string, std::vector<std::string>> connection;
        std::unordered_map<std::string, std::vector<Villager>> villager_place;
        std::unordered_map<std::string, std::unordered_map<Item, int>> item_place;
};

#endif //MAP_H