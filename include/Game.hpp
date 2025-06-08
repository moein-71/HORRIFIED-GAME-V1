#ifndef Game_HPP
#define Game_HPP

#include <memory> 
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <ctime>
#include <random>
#include <stdexcept>
#include <format>
#include <array>
#include <set>

class CharacterState ;
class Map ;
class Archaeologist ;
class Mayor ;
class Dracula ;
class Invisible_man ;
class Villager ;
class Perk ;
class Item ;
class Monster_card ;

class Game {

    friend class Move_monster ;
    friend class Kill ;
    friend class Power ;

    public :

        Game() ;
        
        int random_number() ;
        Item get_random_item() ; 
        shared_ptr<Perk> get_random_perk() ; 
        shared_ptr<Monster_card> get_random_monster_card() ;
        Villager get_villager(std::string name) ;
        char throw_dice() ; 
        std::string find_place_with_more_item_map() ;
        bool remove_all_item_in_place(std::string place) ;

        void set_invisible_man_place(const std::string place) ;
        void set_dracula_place(const std::string place) ;
        void set_last_hero_turn(const std::string & new_turn) ;
        void set_mayor_place(const std::string & place) ;
        void set_archaeologist_place(const std::string & place) ;
        void set_frenzy_monster(const std::string & name) ;
        std::string get_invisible_man_place() ;
        std::string get_dracula_place() ;
        std::string get_last_hero_turn() ;
        std::string get_mayor_place() ;
        std::string get_archaeologist_place() ;
        std::string get_frenzy_monster() ;
        std::string get_dracula_name() ;
        std::string get_invisible_man_name() ;

    private :
    
        std::unique_ptr<CharacterState> turn ;
        std::string last_hero_turn ; // Archaeologist , Mayor  // in constructor we find out how start first and ho start last and its use in monster card abilitys
        Map Game_map ;
        int Terror_level ;
        Archaeologist archaeologist ;
        Mayor mayor ;
        Dracula dracula ;  
        Invisible_man invisible_man ; 
        std::string frenzy_monster ; // first dracula // name of the monsters save in it 
        std::vector<Villager> villagers_bag ;
        std::vector<shared_ptr<Perk>> perk_bag ;
        std::vector<shared_ptr<Monster_card>> Monster_cards_bag ;
        std::vector<Item> item_bag ;
} ;

#endif //Game_HPP