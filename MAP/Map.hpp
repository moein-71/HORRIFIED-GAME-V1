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
        bool set_villager_place(std::string, std::string, std::string);//This function edit villager_place

        bool Kill_Villager(std::string); 
        Item Pickeup_Item(std::string, std::string);
        std::string Find_Place_With_More_Item();
        std::vector<pair<Item, int>> Remove_All_Item_In_Place(std::string);
        std::string Find_Near_Destination(int, std::string, Archaologist, Mayor);
        std::string Move_Monster_Away_From_Hero(std::string, Hero*, Hero*); // where is move 
        std::string Move_Hero_Away_From_Monsters( // where is move 
            const std::string& hero_location,
            const std::string& monster1_location,
            const std::string& monster2_location,
            const std::string& other_hero_location,
            const int max_steps = 2
        );
        int bfs_distance(const std::string& start, const std::string& end);

    private:

        std::unordered_map<std::string, std::vector<std::string>> connection;
        std::unordered_map<std::string, std::vector<Villager>> villager_place;
        std::unordered_map<std::string, std::unordered_map<Item, int>> item_place;
};

#endif //MAP_H