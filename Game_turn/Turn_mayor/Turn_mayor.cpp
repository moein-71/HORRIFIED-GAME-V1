#include "Turn_mayor.hpp"
#include "Turn_monster.hpp"

using namespace std ;

bool Turn_mayor::phase(Game& gamestage) {
    gamestage.set_last_hero_turn(gamestage.archaologist.get_name()) ;
    gamestage.turn->handle_turn(gamestage) ;
    shared_ptr<Hero_Action> action ;
    
    int remain_actions = gamestage.mayor.get_action() + gamestage.get_added_action() ;

    int choose = 0 ;

    while(action > 0) {
        cout<< "Remain actions : " << remain_actions
        << "1.Move  2.Guide  3.Pick up  4.Advance  5.Defeat  6.Special Action  7.Use perk\n"
        << "\nChoose your action :" ;
        cin>> choose ;

        switch(choose)
        {
            case 1:
                action = make_shared<Move_Hero>() ;
                if(action -> Activate(gamestage , &gamestage.mayor)) {
                    remain_actions-- ;
                    cout<< "Move done\n" ;
                }
                cout<< "Move not done\n" ;
                break;
            case 2:
                action = make_shared<Guide>() ;
                if(action -> Activate(gamestage , &gamestage.mayor)) {
                    remain_actions-- ;
                    cout<< "Guide done\n" ;
                }
                cout<< "Guide not done\n" ;
                break;
            case 3:
                action = make_shared<Pick_Up>() ;
                if(action -> Activate(gamestage , &gamestage.mayor)) {
                    remain_actions-- ;
                    cout<< "Pick_Up done\n" ;
                }
                cout<< "Pick_Up not done\n" ;
                break;
            case 4:
                action = make_shared<Advance>() ;
                if(action -> Activate(gamestage , &gamestage.mayor)) {
                    remain_actions-- ;
                    cout<< "Advance done\n" ;
                }
                cout<< "Advance not done\n" ;
                break;
            case 5:
                action = make_shared<Defeat>() ;
                if(action -> Activate(gamestage , &gamestage.mayor)) {
                    remain_actions-- ;
                    cout<< "Defeat done\n" ;
                }
                cout<< "Defeat not done\n" ;
                break;
            case 6:
                cout<< "Mayor dont have Special_Action" ;
                break;
            case 7:
                gamestage.archaologist.get_perk()->ability(gamestage) ;
                break;
            default:
                cout<< "\nChooss right number\n" ;
                continue;
        }
    }
}

void Turn_mayor::handle_turn(Game& gamestage) {

    gamestage.turn = gamestage.monster ;
}
