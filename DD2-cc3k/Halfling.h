#ifndef HALFLING_H
#define HALFLING_H
#include "Enemies.h"
#include <memory>
#include <string>

class Player; 

class Halfling: public Enemies {
    public: 
        Halfling(); // Constructor
        ~Halfling(); // Destructor
        // called when attacking the player, return a displayable texts that summarize what happened
        virtual std::string attack(std::shared_ptr<Player> player) override; 
}; 

#endif
