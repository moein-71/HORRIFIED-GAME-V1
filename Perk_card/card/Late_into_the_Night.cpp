#include "Late_into_the_Night.hpp"

using namespace std ;

void Late_into_the_night::ability(Game& gamestage) {

    const int added_action = 2 ;

    gamestage.set_added_action(added_action) ; 
}

std::string Late_into_the_night::info() const {

    cout<< "add two action to now turn player actions\n" ;
}
