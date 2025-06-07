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
        Villager get_villager(string name) ;
        char throw_dice() ; 

        void set_invisible_man_place(string place) ;
        void set_dracula_place(string place) ;
        void set_last_hero_turn(string new_turn) ;
        void set_mayor_place(string place) ;
        void set_archaeologist_place(string place) ;
        string get_invisible_man_place() ;
        string get_dracula_place() ;
        string get_last_hero_turn() ;
        string get_mayor_place() ;
        string get_archaeologist_place() ;

    private :
    
        std::unique_ptr<CharacterState> turn ;
        std::string last_hero_turn ; // Archaeologist , Mayor  // in constructor we find out how start first and ho start last and its use in monster card abilitys
        Map Game_map ;
        int Terror_level ;
        Archaeologist archaeologist ;
        Mayor mayor ;
        Dracula dracula ;  
        Invisible_man invisible_man ; 
        std::vector<Villager> villagers_bag ;
        std::vector<shared_ptr<Perk>> perk_bag ;
        std::vector<shared_ptr<Monster_card>> Monster_cards_bag ;
        std::vector<Item> item_bag ;
} ;

#endif //Game_HPP