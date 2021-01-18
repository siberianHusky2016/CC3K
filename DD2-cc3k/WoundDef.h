#ifndef WOUNDDEF_H
#define WOUNDDEF_H
#include "Potions.h" 
#include <string>
#include <memory>
#include "Items.h"

class Player; 

class WoundDef: public Potions, public Items{
    public: 
        // Constructor
        WoundDef(); 
        // Destructor
        ~WoundDef(); 
        // apply effects of a potion to the player, returns a string that summarize what happened
        virtual std::string applyEffect(std::shared_ptr<Player> player) override;  
        // return "potion"
        virtual std::string getIdentity() override; 
}; 

#endif
