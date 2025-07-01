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
    // this -> showWelcomeScreen() ;

    for(int i{} ; i < 12 ; ++i) {
        base_game.set_item_to_map(base_game.get_random_item()) ;
    }

    printLineDelay("\nEnter name for Player 1 :") ;
    string player_1 ;
    int garlic_player_1 ;
    cin>> player_1 ;

    printLineDelay("\n\nEnter name for Player 2 :") ;
    string player_2 ;
    int garlic_player_2 ;
    cin>> player_2 ;

    cin.ignore() ;
    cout<< "\n" ;
    printLineDelay(player_1) ;
    printLineDelay("how many days ago you eat garlic ? ") ;
    garlic_player_1 = this -> CheckInputNumber() ;

    cout<< "\n" ;
    printLineDelay(player_2) ;
    printLineDelay("how many days ago you eat garlic ? ") ;
    garlic_player_2 = this -> CheckInputNumber() ;

    if(garlic_player_1 > garlic_player_2) {
        swap(player_1 , player_2) ;
        swap(garlic_player_1 , garlic_player_2) ;
    }

    while(1){
        printLineDelay(player_1) ;
        printLineDelay("\nChoose your hero 1.Mayer of 2.Archaologist ? ") ;
        auto mayor = std::make_shared<Turn_mayor>();
        auto archaologist = make_shared<Turn_archaologist>() ;

        char choose ;
        cin>> choose ;
        if(choose == '1') {
            this -> base_game.set_player_1(mayor) ;
            this -> base_game.set_player_2(archaologist) ;
            this -> base_game.mayor.set_player_name(player_1) ;
            this -> base_game.archaologist.set_player_name(player_2) ;
            break ;
        }
        else if(choose == '2') {
            this -> base_game.set_player_1(archaologist) ;
            this -> base_game.set_player_2(mayor) ;
            this -> base_game.mayor.set_player_name(player_2) ;
            this -> base_game.archaologist.set_player_name(player_1) ;
            break ;
        }
    }
}

void Program::Run() {

    this -> base_game.Game_map.Print_Map_And_All_Info(this->base_game.get_archaologist_place() , this->base_game.get_mayor_place() , this->base_game.get_dracula_place() , this->base_game.get_invisible_man_place() , this->base_game.dracula.get_casket() , this->base_game.invisible_man.get_investigate() ) ;
    
    
    if(!this -> base_game.turn->phase(this -> base_game)) {
        throw logic_error("somthing in phase goes wrong\n") ;
    }
    if(!this -> base_game.turn->phase(this -> base_game)) {
        throw logic_error("somthing in phase goes wrong\n") ;
    }
}

bool Program::End() {
    if(base_game.get_monster_card_number() == 0) {
        printLineDelay("\n\nMONSTER SIDE WINS\n\n" , 100) ;
        return true ;
    }
    else if(base_game.get_Terror_level() == 5) {
        printLineDelay("\n\nMONSTER SIDE WINS\n\n" , 100) ;
        return true ;
    }
    else if(base_game.get_dracula_place() == "DEAD" && base_game.get_invisible_man_place() == "DEAD") {
        printLineDelay("\n\nHERO SIDE WINS\n\n" , 100) ;
        return true ;
    }
    else {
        return false ;
    }
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


int Program::CheckInputNumber() {
    int number;
    std::string input;

    while (true) {
        printLineDelay("Please enter a number: ");
        std::getline(std::cin, input);

        std::stringstream ss(input);

        if (ss >> number && ss.eof()) {
            return number ;
            break;
        } else {
            std::cout << "Invalid input. Please try again.\n";
        }
    }
}
