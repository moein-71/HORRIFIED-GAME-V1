#ifndef MAYOR_H
#define MAYOR_H

#include "Hero.hpp"

class Mayor: public Hero{

    public:

        Mayor(): Hero("Mayor", "Theater", 0, 5){};
};

#endif//MAYOR_H