#include "Overstock.hpp"

using namespace std ;


void Overstock::ability(Game& gamestage)  {

    const int player = 2 ;

    for(int i{} ; i < 2 ; ++i) {
        gamestage.set_item_to_map(gamestage.get_random_item()) ;
    }
}

std::string Overstock::info() const  {
    
    cout<< "every player pick an item and placed in its location \n" ; 
}