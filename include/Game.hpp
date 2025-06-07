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

    friend class Form_of_The_bat ;
    friend class Sunrise ;

    public :

        Game() ;
        
        int random_number() ;
        Item get_random_item() ; 
        shared_ptr<Perk> get_random_perk() ; 
        shared_ptr<Monster_card> get_random_monster_card() ;
        Villager get_villager(string name) ;
        char throw_dice() ; 

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