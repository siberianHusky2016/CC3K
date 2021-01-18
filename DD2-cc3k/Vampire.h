#ifndef VAMPIRE_H
#define VAMPIRE_H
#include "Player.h"
#include <memory>
#include <string>

class Enemies; 

class Vampire: public Player {
    public: 
        Vampire(); // Constructor
        ~Vampire(); // Destructor
        // called when attacking an enemy, return a displayable texts that summarize what happened
        // implemented special abilities of Vampire
        virtual std::string attack(std::shared_ptr<Enemies> enemy) override; 
}; 

#endif
