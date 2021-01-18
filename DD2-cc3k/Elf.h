#ifndef ELF_H
#define ELF_H
#include "Enemies.h"
#include <memory>
#include <string>

class Player; 

class Elf: public Enemies {
    public: 
        Elf(); // Constructor
        ~Elf(); // Destructor
        // called when attacking the player, return a displayable texts that summarize what happened
        virtual std::string attack(std::shared_ptr<Player> player) override; //called when attacking an enemy
}; 

#endif
