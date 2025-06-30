#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "../Game/Game.hpp"
#include <sstream>

class Program {
    
    public : 

        void Start() ;
        void Run() ;
        bool End() ; //if game has been end return true 

        void printLineDelay(const std::string& line, int delayMs = 50) ;
        void showWelcomeScreen() ;

    private : 

        std::string player_1 ;
        std::string player_2 ;
        Game base_game ;
} ;

#endif //PROGRAM_HPP