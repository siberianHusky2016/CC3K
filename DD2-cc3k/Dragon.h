#ifndef DRAGON_H
#define DRAGON_H
#include "Enemies.h"
#include <memory>
#include <string>

class Player; 

class Dragon: public Enemies {
    public: 
        Dragon(); // Constructs a Dragon character
        ~Dragon(); // Destructor
        // called when attacking the player, return a displayable texts that summarize what happened
        virtual std::string attack(std::shared_ptr<Player> player) override; 
}; 

#endif
