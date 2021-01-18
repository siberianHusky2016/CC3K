#ifndef HUMAN_H
#define HUMAN_H
#include "Enemies.h"
#include <memory>
#include <cmath>
#include <string>

class Player; 

class Human: public Enemies {
    public: 
        Human(); // Constructor
        ~Human(); // Destructor
        // called when attacking the player, return a displayable texts that summarize what happened
        virtual std::string attack(std::shared_ptr<Player> player) override; 
}; 

#endif

