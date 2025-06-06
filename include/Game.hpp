#ifndef Game_HPP
#define Game_HPP

#include <memory> 
#include <vector>

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

        Item random_item() ; 
        Perk random_perk() ; 
        Monster_card random_monster_card() ;

    private :
    
        std::unique_ptr<CharacterState> turn ;
        Map Game_map ;
        int Terror_level ;
        Archaeologist archaeologist ;
        Mayor mayor ;
        Dracula racula ;  
        Invisible_man invisible_man ; 
        std::vector<Villager> villagers_bag ;
        std::vector<Perk> perk_bag ;
        std::vector<Item> item_bag ;
        std::vector<Monster_card> Monster_cards_bag ;
} ;

#endif //Game_HPP