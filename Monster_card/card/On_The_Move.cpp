#include "On_The_Move.hpp"
#include "../../Monster_action/Move_monster/Move_monster.hpp"
#include "../../Monster_action/Kill/Kill.hpp"
#include "../../Monster_action/Power/Power.hpp"

using namespace std ;

void On_the_move::ability(Game& gamestage) {
    constexpr int add_item = 3 ;
    constexpr int move = 3 ;
    constexpr int dice_number = 2 ;
    constexpr int strike_number = 1 ;

    //Item
    
    for(int i{} ; i < add_item ; ++i) {
        gamestage.set_item_to_map(gamestage.get_random_item()) ;
    }

    //Event 
    
    //Strike

    array<string , strike_number> monster_turn {gamestage.get_frenzy_monster()} ;

    unique_ptr<Monster_action> action = make_unique<Move_monster>() ;

    vector<shared_ptr<Power>> invisible_man_power ;

    bool kill = false ; 

    for(int i{} ; i < strike_number ; ++i ) {

        if(monster_turn[i] == gamestage.get_dracula_name()) {
            if(gamestage.get_dracula_place() == "DEAD") {
                continue ;
            }
        }

        if(monster_turn[i] == gamestage.get_invisible_man_name()) {
            if(gamestage.get_invisible_man_place() == "DEAD") {
                continue ;
            }
        }

        if(kill) break ;

        //Move 
        action = make_unique<Move_monster>() ;
        for(int j{} ; j < move ; ++j) {
            action->activate(gamestage , monster_turn[i]) ;
        }
        gamestage.printLineDelay(monster_turn[i] + " move to " + (monster_turn[i] == gamestage.get_dracula_name() ? gamestage.get_dracula_place() : gamestage.get_invisible_man_place())) ;

        //Dice
        set<char> dice ;

        for(int j{} ; j < dice_number ; ++j) {
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

void On_the_move::info() const {
    cout<< "\nOn_The_Move\n"
    << "add 3 item"
    << "closest villager or hero get closer on block\n" 
    << "Strike : 3 Move , 2 Dice\n" 
    << "Turn : Frenzied Monster\n" ;
}
