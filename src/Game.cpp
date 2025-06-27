#include "Game.hpp"

#include "Perk_card.hpp"
#include "Break_of_Dawn.hpp"
#include "Hurry.hpp"
#include "Late_into_the_Night.hpp"
#include "Overstock.hpp"
#include "Repel.hpp"
#include "Visit_from_the_Detective.hpp"

#include "Egyptian_Expert.hpp"
#include "Former_Employer.hpp"
#include "Form_of_The_Bat.hpp"
#include "Fortune_Teller.hpp"
#include "Hurried_Assistant.hpp"
#include "Sunrise.hpp"
#include "The_Delivery.hpp"
#include "The_Ichthyologist.hpp"
#include "The_Innocent.hpp"
#include "Thief.hpp"

using namespace std ;

// std::vector<Villager> villagers_bag ;
// std::vector<Item> item_bag ;

Game::Game() {////////////////////////////////////////////////// will be completed

    this->set_frenzy_monster(this->get_dracula_name()) ;

    perk_bag.emplace_back(make_shared<Break_of_dawn>) ;
    perk_bag.emplace_back(make_shared<Hurry>) ;
    perk_bag.emplace_back(make_shared<Late_into_the_night>) ;
    perk_bag.emplace_back(make_shared<Overstock>) ;
    perk_bag.emplace_back(make_shared<Repel>) ;
    perk_bag.emplace_back(make_shared<Visit_from_the_detective>) ;

    Monster_cards_bag.emplace_back(make_shared<Egyptian_expert>) ;
    Monster_cards_bag.emplace_back(make_shared<Form_of_The_bat>) ;
    Monster_cards_bag.emplace_back(make_shared<Former_employer>) ;
    Monster_cards_bag.emplace_back(make_shared<Fortune_teller>) ;
    Monster_cards_bag.emplace_back(make_shared<Hurried_assistant>) ;
    Monster_cards_bag.emplace_back(make_shared<Sunrise>) ;
    Monster_cards_bag.emplace_back(make_shared<The_delivery>) ;
    Monster_cards_bag.emplace_back(make_shared<The_ichthyologist>) ;
    Monster_cards_bag.emplace_back(make_shared<The_innocent>) ;
    Monster_cards_bag.emplace_back(make_shared<Thief>) ;

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

void Game::set_item_to_map(Item new_item) {

    this->Game_map.set_item(new_item) ;
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

void Game::handle_next_turn() {
    this -> next_turn.handle_turn() ;
}

void Game::print_map() {
    this -> Game_map.print() ;
}

string Game::find_far_destination_monster_map(int move , std::string place , std::string archaeologist_place , std::string mayor_place) {
    return this -> Game_map.find_far_destination_monster(move , place , this -> archaeologist , this -> mayor) ;
}

std::string Game::find_far_destination_hero_map(int move , std::string place , std::string dracula_place , std::string Invisible_man_place) {
    return this -> Game_map.find_far_destination_hero(move , place , this -> dracula , this -> invisible_man) ;

}


bool Game::set_invisible_man_place(const string place) {
    return this->invisible_man.set_now_place(place) ;
}

bool Game::set_dracula_place(const string place) {
    return this->dracula.set_now_place(place) ;
}

void Game::set_last_hero_turn(const string & new_turn) {
    this->last_hero_turn = new_turn ;
}

bool Game::set_mayor_place(const string & place) {
    return this->mayor.set_now_place(place) ;
}

bool Game::set_archaeologist_place(const string & place) {
    return this->archaeologist.set_now_place(place) ;

}

bool Game::set_frenzy_monster( const string & name) {
    return this->frenzy_monster = name ;
}

void Game::set_villager_in_Game_map(const std::string place , const std::string name) {

    for(int counter{} ; Villager temp : this->villagers_bag) {
        if(temp.get_name() == name) {
            if(this->Game_map.set_villager(place , temp)) {
                villagers_bag.erase(villagers_bag.begin() + counter) ;
                return ;
            }
            else if(this->Game_map.set_villager_place(place , name)) {
                return ;
            }
            else {
                cout<< "\nsorry but this villager has been died\n" ;
            }
        }
        ++counter ;
    }
}

void Game::set_added_action(const int & added_action) {
    this -> added_action = added_action ;
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
int Game::get_added_action() {
    return this -> added_action ;
}



