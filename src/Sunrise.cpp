#include "Sunrise.hpp"

using namespace std ;

void Sunrise::ability(Game& gamestage) {

    //Event
    gamestage.dracula.set_now_place("Crypt") ; /////////////////// check place names

    //Strike

    constexpr int move = 1 ;
    constexpr int dice_number = 2 ;

    gamestage.invisible_man.set_now_place(gamestage.Game_map.find_destination(move , gamestage.invisible_man.get_now_place() , gamestage.mayor.get_now_place() , gamestage.archaeologist.get_now_place())) ;

    set<char> dice ;

    for(int i{} ; i < dice_number ; ++i) {
        dice.insert(gamestage.throw_dice()) ;
    }

    for(char chance : dice) {
        if(chance == 'K') {
            if(gamestage.Game_map.kill_villager(gamestage.invisible_man.get_now_place())) {
                return ;
            }
            else {
                continue;
            }
        }
        else if(chance == 'P') {
            gamestage.invisible_man.set_now_place(gamestage.Game_map.find_destination(2 , gamestage.invisible_man.get_now_place() , "none" , "none")) ;
        }
        else if(chance == 'N') {
            break ;
        }
    }

}

std::string Sunrise::info() const {
    cout<< "Dracula moved to the Crypt\n" ;
    cout<< "Strike : 1 Move , 2 Dice\n" ;
    cout<< "Turn : Invisible Man , Frenzied Monster \n" ;
}