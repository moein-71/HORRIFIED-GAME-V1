#ifndef MAP_H
#define  MAP_H

#include "../VILLAGER/Villager.hpp"
#include "../ITEM/Item.hpp"
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

    private:

        std::unordered_map<std::string, std::vector<std::string>> connection;
        std::unordered_map<std::string, std::vector<Villager>> villager_place;
        std::unordered_map<std::string, std::unordered_map<Item, int>> item_place;
};

#endif //MAP_H