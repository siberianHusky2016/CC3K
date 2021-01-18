#ifndef DROW_H
#define DROW_H
#include "Player.h"
#include <memory>
#include <string>

class Enemies; 

class Drow: public Player {
    public: 
        Drow(); //constructs the Drow character
        ~Drow(); // Destructor
}; 

#endif

