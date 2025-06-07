#include "Sunrise.hpp"
#include "Move_monster.hpp"
#include "Kill.hpp"
#include "Power.hpp"

using namespace std ;

void Sunrise::ability(Game& gamestage) {

    //Event
    gamestage.set_dracula_place("Crypt") ; /////////////////// check place names

    //Strike

    constexpr int move = 1 ;
    constexpr int dice_number = 2 ;

    unique_ptr<Monster_action> action = make_unique<Move_monster>() ;

    vector<shared_ptr<Power>> invisible_man_power ;

    // invisible man turn 

    for(int i{} ; i < move ; ++i) {
        action->activate(gamestage , gamestage.get_invisible_man_name()) ;
    }


    set<char> dice ;

    for(int i{} ; i < dice_number ; ++i) {
        dice.insert(gamestage.throw_dice()) ;
    }

    for(char chance : dice) {
        if(chance == 'K') {
            action = make_unique<Kill>() ;
            if(action->activate(gamestage , gamestage.get_invisible_man_name())) {
                return ;
            }
            else {
                continue;
            }
        }
        else if(chance == 'P') {
            invisible_man_power.push_back(make_shared<Power>()) ;
        }
        else if(chance == 'N') {
            break ;
        }
    }

    //frenzy monster turn 

    for(int i{} ; i < move ; ++i) {
        action->activate(gamestage , gamestage.get_frenzy_monster()) ;
    }

    set<char> dice ;

    for(int i{} ; i < dice_number ; ++i) {
        dice.insert(gamestage.throw_dice()) ;
    }

    for(char chance : dice) {
        if(chance == 'K') {
            action = make_unique<Kill>() ;
            if(action->activate(gamestage , gamestage.get_frenzy_monster())) {
                return ;
            }
            else {
                continue;
            }
        }
        else if(chance == 'P') {
            if(gamestage.get_frenzy_monster() == gamestage.get_invisible_man_name()) {
                invisible_man_power.push_back(make_shared<Power>()) ;
            }
            else if(gamestage.get_frenzy_monster() == gamestage.get_dracula_name()) {
                action = make_unique<Power>() ;
                action->activate(gamestage , gamestage.get_frenzy_monster()) ;
            }
            else {
                throw invalid_argument("somthing in ability sunrise goes wrong") ;
            }
        }
        else if(chance == 'N') {
            break ;
        }
    }

    for(auto active_power : invisible_man_power) {
        active_power->activate(gamestage , gamestage.get_invisible_man_name()) ;
    }
}

std::string Sunrise::info() const {
    cout<< "Dracula moved to the Crypt\n" ;
    cout<< "Strike : 1 Move , 2 Dice\n" ;
    cout<< "Turn : Invisible Man , Frenzied Monster \n" ;
}