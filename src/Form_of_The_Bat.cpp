#include "Form_of_The_Bat.hpp" 
#include "Move_monster.hpp"
#include "Kill.hpp"
#include "Power.hpp"

using namespace std ;

class Invisible_man {};

void Form_of_The_bat::ability(Game& gamestage) {

    //Event 

    string dracula_new_place = gamestage.get_last_hero_turn() == "Mayor" ? gamestage.get_mayor_place() : gamestage.get_archaeologist_place() ;
    gamestage.set_dracula_place(dracula_new_place) ;

    //Strike

    constexpr int move = 1 ;
    constexpr int dice_number = 2 ;

    unique_ptr<Monster_action> action = make_unique<Move_monster>() ;

    for(int i{} ; i < move ; ++i) {
        action->activate(gamestage , "invisible_man") ;
    }

    set<char> dice ;

    for(int i{} ; i < dice_number ; ++i) {
        dice.insert(gamestage.throw_dice()) ;
    }

    for(char chance : dice) {
        if(chance == 'K') {
            action = make_unique<Kill>() ;
            if(action->activate(gamestage , "invisible_man")) {
                return ;
            }
            else {
                continue;
            }
        }
        else if(chance == 'P') {
            action = make_unique<Power>() ;
            action->activate(gamestage , "invisible_man") ;
        }
        else if(chance == 'N') {
            break ;
        }
    }
}

std::string Form_of_The_bat::info() const {
    cout<< "Dracula moved to the last Hero who has played\n" ;
    cout<< "Strike : 1 Move , 2 Dice\n" ;
    cout<< "Turn : Invisible Man \n" ;
}
