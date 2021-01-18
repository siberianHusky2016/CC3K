#ifndef BOOSTDEF_H
#define BOOSTDEF_H
#include "Potions.h" 
#include <string>
#include <memory>
#include "Items.h"

class Player; 

class BoostDef: public Potions, public Items {
    public: 
        // Constructor
        BoostDef(); 
        // Destructor
        ~BoostDef(); 
        // apply effects of a potion to the player, returns a string that summarize what happened
        virtual std::string applyEffect(std::shared_ptr<Player> player) override;  
        // Get the identity of potion
        virtual std::string getIdentity() override; 
}; 

#endif
