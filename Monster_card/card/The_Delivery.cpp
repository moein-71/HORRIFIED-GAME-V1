#include "The_Delivery.hpp"
#include "Move_monster.hpp"
#include "Kill.hpp"
#include "Power.hpp"

using namespace std ;

void The_delivery::ability(Game& gamestage) {

    constexpr int add_item = 3 ;
    constexpr int move = 1 ;
    constexpr int dice_number = 3 ;
    constexpr int strike_number = 1 ;

    //Item
    
    for(int i{} ; i < add_item ; ++i) {
        gamestage.set_item_to_map(gamestage.get_random_item()) ;
    }
    
    //Event 

    gamestage.set_villager_in_Game_map("Docks" , "Wilbur & Chick") ;
    
    //Strike

    array<string , strike_number> monster_turn {gamestage.get_frenzy_monster()} ;

    unique_ptr<Monster_action> action = make_unique<Move_monster>() ;

    vector<shared_ptr<Power>> invisible_man_power ;

    bool kill = false ; 

    for(int i{} ; i < strike_number ; ++i ) {

        if(kill) break ;

        //Move 
        action = make_unique<Move_monster>() ;
        for(int i{} ; i < move ; ++i) {
            action->activate(gamestage , monster_turn[i]) ;
        } 

        //Dice
        set<char> dice ;

        for(int i{} ; i < dice_number ; ++i) {
            dice.insert(gamestage.throw_dice()) ;
        }

        for(char chance : dice) {
            if(chance == 'K') { //Kill
                action = make_unique<Kill>() ;
                if(action->activate(gamestage ,monster_turn[i])) {
                    kill = true ;
                    break ;
                }
                else {
                    continue;
                }
            }
            else if(chance == 'P') { //Power 
                if(monster_turn[i] == gamestage.get_invisible_man_name()) {
                    invisible_man_power.push_back(make_shared<Power>()) ;
                    break ;
                }
                else if(monster_turn[i] == gamestage.get_dracula_name()) {
                    action = make_unique<Power>() ;
                    action->activate(gamestage , gamestage.get_frenzy_monster()) ;
                    break ;
                }
                else {
                    throw invalid_argument("somthing in ability sunrise goes wrong") ;
                }
            }
            else if(chance == 'Z') {
                break ;
            }
        }
    }

    action = make_unique<Power>() ;
    for(auto active_power : invisible_man_power) {
        active_power->activate(gamestage , gamestage.get_invisible_man_name()) ;
    }
}

std::string The_delivery::info() const {
    cout<< "\nThe_Delivery\n"
    << "add 3 item"
    << "Wilbur & Click are goes to Docks\n" 
    << "Strike : 1 Move , 3 Dice\n" 
    << "Turn : Frenzied Monster\n" ;
}
