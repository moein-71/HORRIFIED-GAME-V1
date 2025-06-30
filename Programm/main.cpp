#include "Programm.hpp"

using namespace std ;

int main() {

    Program p ;
    p.Start() ;

    while (!p.End())
    {
        p.Run() ;
    }

    return 0 ;
}
