#ifndef GOBLIN_H
#define GOBLIN_H
#include "Player.h"
#include <memory>
#include <cmath>
#include <string>

class Enemies; 

class Goblin: public Player {
    public: 
        Goblin();  // Constructor
        ~Goblin(); // Destructor
        // called when attacking an enemy, return a displayable texts that summarize what happened
        virtual std::string attack(std::shared_ptr<Enemies> enemy) override; 
}; 

#endif
