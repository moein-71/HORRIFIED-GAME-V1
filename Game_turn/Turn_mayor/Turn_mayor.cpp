#include "Turn_mayor.hpp"
#include "../Turn_monster/Turn_monster.hpp"

using namespace std ;

bool Turn_mayor::phase(Game& gamestage) {
    gamestage.set_last_hero_turn(gamestage.mayor.get_name()) ;
    gamestage.turn->handle_turn(gamestage) ;
    shared_ptr<Hero_Action> action ;
    
    int remain_actions = gamestage.mayor.get_action() + gamestage.get_added_action() ;

    int choose = 0 ;

    while(action > 0) {
        cout<< "Remain actions : " << remain_actions
        << "1.Move  2.Guide  3.Pick up  4.Advance  5.Defeat  6.Special Action  7.Use perk\n"
        << "\nChoose your action :" ;
        cin>> choose ;

        if(choose == '1') {
            action = make_shared<Move_Hero>() ;
            if(action -> Activate(gamestage , &gamestage.archaologist)) {
                remain_actions-- ;
                cout<< "Move done\n" ;
            }
            cout<< "Move not done\n" ;
        }
        else if(choose == '2') {
            action = make_shared<Guide>() ;
            if(action -> Activate(gamestage , &gamestage.archaologist)) {
                remain_actions-- ;
                cout<< "Guide done\n" ;
            }
            cout<< "Guide not done\n" ;
        }
        else if(choose == '3') {
            action = make_shared<Pick_Up>() ;
            if(action -> Activate(gamestage , &gamestage.archaologist)) {
                remain_actions-- ;
                cout<< "Pick_Up done\n" ;
            }
            cout<< "Pick_Up not done\n" ;
        }
        else if(choose == '4') {
            action = make_shared<Advance>() ;
            if(action -> Activate(gamestage , &gamestage.archaologist)) {
                remain_actions-- ;
                cout<< "Advance done\n" ;
            }
            cout<< "Advance not done\n" ;
        }
        else if(choose == '5') {
            action = make_shared<Defeat>() ;
            if(action -> Activate(gamestage , &gamestage.archaologist)) {
                remain_actions-- ;
                cout<< "Defeat done\n" ;
            }
            cout<< "Defeat not done\n" ;
        }
        else if(choose == '6') {
             cout<< "Mayor dont have Special_Action" ;
        }
        else if(choose == '7') {
            auto perk_variant = gamestage.archaologist.get_perk();
            if (auto perk_ptr = std::get_if<std::shared_ptr<Perk_card>>(&perk_variant)) {
                (*perk_ptr)->ability(gamestage);
            }
        }
        else {
            cout<< "\nChooss right number\n" ;
            continue;
        }
    }
}

void Turn_mayor::handle_turn(Game& gamestage) {

    gamestage.turn = gamestage.monster ;
}
