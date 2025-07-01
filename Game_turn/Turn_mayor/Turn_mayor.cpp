#include "Turn_mayor.hpp"
#include "../Turn_monster/Turn_monster.hpp"

using namespace std ;

bool Turn_mayor::phase(Game& gamestage) {

    gamestage.mayor.Print_Hero_Info() ;
    gamestage.set_last_hero_turn(gamestage.mayor.get_name()) ;
    gamestage.turn->handle_turn(gamestage) ;
    shared_ptr<Hero_Action> action = nullptr ;
    
    int remain_actions = gamestage.mayor.get_action() + gamestage.get_added_action() ;

    char choose = 0 ;

    while(remain_actions > 0) {
        gamestage.printLineDelay("Remain actions : " + to_string(remain_actions) + '\n' + "1.Move  2.Guide  3.Pick up  4.Advance  5.Defeat  6.Special Action  7.Use perk  8.status\n" + "\nChoose your action : " );
        cin>> choose ;

        if(choose == '1') {
            action = make_shared<Move_Hero>() ;
            if(action -> Activate(gamestage , &gamestage.mayor)) {
                remain_actions-- ;
                gamestage.printLineDelay("Move done\n") ;
                continue;
            }
            gamestage.printLineDelay( "Move not done\n") ;
        }
        else if(choose == '2') {
            action = make_shared<Guide>() ;
            if(action -> Activate(gamestage , &gamestage.mayor)) {
                remain_actions-- ;
                gamestage.printLineDelay("Guide done\n") ;
                continue;
            }
            gamestage.printLineDelay("Guide not done\n") ;
        }
        else if(choose == '3') {
            action = make_shared<Pick_Up>() ;
            if(action -> Activate(gamestage , &gamestage.mayor)) {
                remain_actions-- ;
                gamestage.printLineDelay("Pick_Up done\n") ;
                continue;
            }
            gamestage.printLineDelay("Pick_Up not done\n") ;
        }
        else if(choose == '4') {
            action = make_shared<Advance>() ;
            if(action -> Activate(gamestage , &gamestage.mayor)) {
                remain_actions-- ;
                gamestage.printLineDelay("Advance done\n") ;
                continue;
            }
            gamestage.printLineDelay("Advance not done\n") ;
        }
        else if(choose == '5') {
            action = make_shared<Defeat>() ;
            if(action -> Activate(gamestage , &gamestage.mayor)) {
                remain_actions-- ;
                gamestage.printLineDelay("Defeat done\n") ;
                continue;
            }
            gamestage.printLineDelay("Defeat not done\n") ;
        }
        else if(choose == '6') {
             gamestage.printLineDelay("Mayor dont have Special_Action\n") ;
             continue;
        }
        else if(choose == '7') {
            auto perk_variant = gamestage.mayor.get_perk();
            if (auto perk_ptr = std::get_if<std::shared_ptr<Perk_card>>(&perk_variant)) {
                (*perk_ptr)->ability(gamestage);
                continue;
            }
        }
        else if(choose == '8') {
            gamestage.Game_map.Print_Map_And_All_Info(gamestage.get_archaologist_place() , gamestage.get_mayor_place() , gamestage.get_dracula_place() , gamestage.get_invisible_man_place() , gamestage.dracula.get_casket() , gamestage.invisible_man.get_investigate() , gamestage.get_Terror_level()) ;
            gamestage.mayor.Print_Hero_Info() ;
        }
        else {
            gamestage.printLineDelay("\nChooss right number\n") ;
            continue;
        }
    } 
    if(remain_actions == 0) {
        return true ;
    }
    else {
        return false ;
    }
}

void Turn_mayor::handle_turn(Game& gamestage) {

    gamestage.turn = gamestage.monster ;
}
