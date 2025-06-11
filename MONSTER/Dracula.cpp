#include "Dracula.hpp"
#include <iostream>
#include <bits/stdc++.h>

Dracula::Dracula(): Monster(1, "Dracula", {"Cave", "Dungeon", "Crypt", "Graveyard"}){
            
    casket["Cave"] = 1; 
    casket["Dungeon"] = 1; 
    casket["Crypt"] = 1; 
    casket["Graveyard"] = 1; 
};