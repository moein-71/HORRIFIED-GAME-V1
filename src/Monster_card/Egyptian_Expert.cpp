#include "Egyptian_Expert.hpp"
#include "Move_monster.hpp"
#include "Kill.hpp"
#include "Power.hpp"

using namespace std ;

void Egyptian_expert::ability(Game& gamestage) {
    
    //Event 

    gamestage.set_villager_in_Game_map("Cave" , "Prof.Pearson") ;
    
    //Strike

    constexpr int move = 2 ;
    constexpr int dice_number = 2 ;
    constexpr int strike_number = 2 ;

    array<string , strike_number> monster_turn {gamestage.get_dracula_name() , gamestage.get_frenzy_monster()} ;

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

std::string Egyptian_expert::info() const {
    cout<< "Prof.Pearson goes to Cave\n" ;
    cout<< "Strike : 2 Move , 2 Dice\n" ;
    cout<< "Turn : Dracula , Frenzied Monster \n" ;
}



