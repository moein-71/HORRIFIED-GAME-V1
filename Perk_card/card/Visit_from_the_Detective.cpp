#include "Visit_from_the_Detective.hpp"

using namespace std ;

void Visit_from_the_detective::ability(Game& gamestage) {
    
    string place ;
    cout<< "\nWhich place you want to send Invisible Man ?\n" ;
    gamestage.print_map() ;
    cin>> place ;
    
    if(place == "exit") {
        return ;
    }
    while(!gamestage.set_invisible_man_place(place)) { // this func should check the place if its currect return true //
        cin>> place ;
        if(place == "exit") {
        return ;
    }
    }
}

std::string Visit_from_the_detective::info() const {
    cout<< "\nVisit from the Detective\n"
    << "You can move Invisible Man where ever you want\n" ;
}
