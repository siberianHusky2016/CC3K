#ifndef DWARF_H
#define DWARF_H
#include "Enemies.h"
#include <memory>
#include <string>

class Player; 

class Dwarf: public Enemies {
    public: 
        Dwarf(); // Constructor
        ~Dwarf(); // Destructor
        // called when attacking the player, return a displayable texts that summarize what happened
        virtual std::string attack(std::shared_ptr<Player> player) override; //called when attacking an enemy
}; 

#endif
