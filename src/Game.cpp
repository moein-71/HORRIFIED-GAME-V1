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

    int number = (this->random_number() % this->item_bag.size()) ;

    Item random_item = item_bag[number] ;
    item_bag.erase(item_bag.begin() + number) ; // check it
    item_bag.shrink_to_fit() ;

    return random_item ;
}
shared_ptr<Perk> Game::get_random_perk() {

    int number = (this->random_number() % this->perk_bag.size()) ;

    shared_ptr<Perk> random = perk_bag[number] ;
    perk_bag.erase(perk_bag.begin() + number) ;
    perk_bag.shrink_to_fit() ;

    if(random == nullptr) {
        throw runtime_error("in get_random_perk somthing goes wrong \n") ;
    }

    return random ;
} 

shared_ptr<Monster_card> Game::get_random_monster_card() {

    int number = (this->random_number() % this->Monster_cards_bag.size()) ;

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

char Game::throw_dice() {

    array<char , 6> dice {'K' , 'Z' , 'Z' , 'Z' , 'Z' , 'P'} ;

    return dice[this->random_number() % 6] ;
}

std::string Game::find_place_with_more_item_map() {
    return this->Game_map.find_place_with_more_item() ;
}

bool Game::remove_all_item_in_place(std::string place) {
    if(this->Game_map.remove_all_item_in_place(place)) { ;
        return true ;
    }
    return false ;
}

void Game::set_invisible_man_place(string place) {
    this->invisible_man.set_now_place(place) ;
}

void Game::set_dracula_place(string place) {
    this->dracula.set_now_place(place) ;
}

void Game::set_last_hero_turn(const string & new_turn) {
    this->last_hero_turn = new_turn ;
}

void Game::set_mayor_place(const string & place) {
    this->mayor.set_now_place(place) ;
}

void Game::set_archaeologist_place(const string & place) {
    this->archaeologist.set_now_place(place) ;

}

void Game::set_frenzy_monster( const string & name) {
    this->frenzy_monster = name ;
}


string Game::get_invisible_man_place() {
    return this->invisible_man.get_now_place() ;
}

string Game::get_dracula_place() {
    return this->dracula.get_now_place() ;
}


string Game::get_last_hero_turn() {
    return  last_hero_turn ;
}

string Game::get_mayor_place() {
    return mayor.get_now_place() ;
}

string Game::get_archaeologist_place() {
    return archaeologist.get_now_place() ;
}

string Game::get_frenzy_monster() {
    return this->frenzy_monster ;
}

string Game::get_dracula_name() {
    return this->dracula.get_name() ;
}

string Game::get_invisible_man_name() {
    return this->invisible_man.get_name() ;
}


