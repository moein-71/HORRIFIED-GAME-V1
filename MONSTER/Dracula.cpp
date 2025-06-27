#include "Dracula.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

Dracula::Dracula(): Monster(1, "Dracula", {"Cave", "Dungeon", "Crypt", "Graveyard"}){
            
    casket["Cave"] = 1; 
    casket["Dungeon"] = 1; 
    casket["Crypt"] = 1; 
    casket["Graveyard"] = 1; 
};



bool Dracula::Destroy_Casket(string place){

    if(casket.count(place)){

        if(casket[place]){

            casket[place] = 0;
            return true;
        }

        else return false;
    }

    else{

        throw invalid_argument("In this place there is no any casket.");
    }
}
bool Dracula::Check_Casket(){
    return  !casket["Cave"] && !casket["Dungeon"] && !casket["Crypt"] && !casket["Graveyard"];
}