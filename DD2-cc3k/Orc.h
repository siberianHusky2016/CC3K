#ifndef Orc_H
#define Orc_H
#include "Enemies.h"
#include <memory>
#include <string>

class Player; 

class Orc: public Enemies {
    public: 
        Orc(); // Constructor
        ~Orc(); // Destructor
        // called when attacking the player, return a displayable texts that summarize what happened
        virtual std::string attack(std::shared_ptr<Player> player) override; 
}; 

#endif
