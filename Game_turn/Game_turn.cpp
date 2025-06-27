#include "Game_turn.hpp"

using namespace std ;

void Game_turn::set_turn(string turn) {
    this -> turn = turn ;
}

string Game_turn::get_turn() {
    return this -> turn ;
}
