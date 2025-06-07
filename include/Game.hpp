#ifndef Game_HPP
#define Game_HPP

#include <memory> 
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <ctime>
#include <random>

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

    public :

        Game() ;
        
        int random_number() ;
        Item get_random_item() ; 
        shared_ptr<Perk> get_random_perk() ; 
        shared_ptr<Monster_card> get_random_monster_card() ;

    private :
    
        std::unique_ptr<CharacterState> turn ;
        Map Game_map ;
        int Terror_level ;
        Archaeologist archaeologist ;
        Mayor mayor ;
        Dracula racula ;  
        Invisible_man invisible_man ; 
        std::vector<shared_ptr<Villager>> villagers_bag ;
        std::vector<shared_ptr<Perk>> perk_bag ;
        std::vector<shared_ptr<Monster_card>> Monster_cards_bag ;
        std::vector<Item> item_bag ;
} ;

#endif //Game_HPP