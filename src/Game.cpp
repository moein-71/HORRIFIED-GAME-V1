#include "Game.hpp"

using namespace std ;

Game::Game() {////////////////////////////////////////////////// will be completed
    
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
shared_ptr<Perk> Game::get_random_perk() {

    int number = (this->random_number() % this->perk_bag.size())-1 ;

    shared_ptr<Perk> random = perk_bag[number] ;
    perk_bag.erase(perk_bag.begin() + number) ;
    perk_bag.shrink_to_fit() ;

    if(random == nullptr) {
        throw runtime_error("in get_random_perk somthing goes wrong \n") ;
    }

    return random ;
} 

shared_ptr<Monster_card> Game::get_random_monster_card() {

    int number = (this->random_number() % this->Monster_cards_bag.size())-1 ;

    shared_ptr<Monster_card> random = Monster_cards_bag[number] ;
    Monster_cards_bag.erase(Monster_cards_bag.begin() + number) ;
    Monster_cards_bag.shrink_to_fit() ;

    if(random == nullptr) {
        throw runtime_error("in get_random_monster_card somthing goes wrong \n") ;
    }

    return random ;
}

Villager Game::get_villager(string name) {

    for(int counter = 0 ; Villager villager : villagers_bag) {
        if(villager.get_name() == name) {
            villagers_bag.erase( villagers_bag.begin() + counter) ;
            return villager ;
        }
        ++counter ;
    }

    throw runtime_error("in Get_villager somthing goes wrong \n") ;
}