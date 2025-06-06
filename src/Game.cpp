#include "Game.hpp"

#include <memory> 
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <ctime>
#include <random>

using namespace std ;

Game::Game() {
    
}

int Game::random_number() {
    
    random_device rd ;

    default_random_engine eng(rd()) ;

    uniform_int_distribution<int> random_number(1 , 100) ;

    return random_number(eng) ;
}

Item Game::get_random_item() {

    int number = (this->random_number() % this->item_bag.size())-1 ;

    Item random_item = item_bag[number] ;
    item_bag.erase(item_bag.begin() + number) ; // check it
    item_bag.shrink_to_fit() ;

    return random_item ;
}
Perk Game::get_random_perk() {} 
Monster_card Game::get_random_monster_card() {}