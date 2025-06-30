#include "Programm.hpp"
#include "Archaologist.hpp"
#include "Mayor.hpp"

#include "Item.hpp"

#include "Map.hpp"

#include "Dracula.hpp"
#include "Invisible_man.hpp"

#include "Villager.hpp"

#include "../Game_turn/Game_turn.hpp"
#include "../Game_turn/Turn_monster/Turn_monster.hpp"
#include "../Game_turn/Turn_archaeologist/Turn_archaeologist.hpp"
#include "../Game_turn/Turn_mayor/Turn_mayor.hpp"

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

void Program::Start() {
    this -> showWelcomeScreen() ;

    printLineDelay("\nEnter name for Player 1 :") ;
    string player_1 ;
    int garlic_player_1 ;
    cin>> player_1 ;

    printLineDelay("\n\nEnter name for Player 2 :") ;
    string player_2 ;
    int garlic_player_2 ;
    cin>> player_2 ;

    cout<< "\n\n" ;
    printLineDelay(player_1) ;
    printLineDelay(" how many days ago you eat garlic ? ") ;
    cin>> garlic_player_1 ;

    cout<< "\n\n" ;
    printLineDelay(player_2) ;
    printLineDelay(" how many days ago you eat garlic ? ") ;
    cin>> garlic_player_2 ;

    if(garlic_player_1 > garlic_player_2) {
        swap(player_1 , player_2) ;
        swap(garlic_player_1 , garlic_player_2) ;
    }

    while(1){
        printLineDelay("\n\nChoose your hero 1.Mayer of 2.Archaologist ? ") ;
        auto mayor = std::make_shared<Turn_mayor>();
        auto archaologist = make_shared<Turn_archaologist>() ;

        char choose ;
        cin>> choose ;
        if(choose == '1') {
            this -> base_game.set_player_1(mayor) ;
            this -> base_game.set_player_2(archaologist) ;
            break ;
        }
        else if(choose == '2') {
            this -> base_game.set_player_1(archaologist) ;
            this -> base_game.set_player_2(mayor) ;
            break ;
        }
    }
}

void Program::Run() {

}

bool Program::End() {

}

void Program::printLineDelay(const string& line, int delayMs) {
    for (char c : line) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
    cout << endl;
}

void Program::showWelcomeScreen() {
    system("clear");  // Use "cls" on Windows
    cout << R"(

██╗  ██╗ ██████╗ ██████╗ ██████╗ ██╗ ███████╗██╗███████╗██████╗ 
██║  ██║██╔═══██╗██╔══██╗██╔══██╗██║ ██╔════╝██║██╔════╝██╔══██╗
███████║██║   ██║██████╔╝██████╔╝██║ █████╗  ██║█████╗  ██║  ██║
██╔══██║██║   ██║██╔══██╗██╔══██╗██║ ██╔══╝  ██║██╔══╝  ██║  ██║
██║  ██║╚██████╔╝██║  ██║██║  ██║██║ ██║     ██║███████╗██████╔╝
╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝ ╚═╝     ╚═╝╚══════╝╚═════╝ 

    )" << endl;

    printLineDelay("--------------------------------------------------------", 20);
    printLineDelay("              WELCOME TO THE HORRIFIED GAME             ", 40);
    printLineDelay("--------------------------------------------------------", 20);
    cout << endl;

    printLineDelay("Prepare yourself to face unspeakable horrors...", 40);
    printLineDelay("Will you survive the night? Let's find out!", 40);
    cout << endl;

    printLineDelay("Press ENTER to continue...", 30);
    cin.ignore();
}
