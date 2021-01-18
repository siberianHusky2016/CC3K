#ifndef POISONHEALTH_H
#define POISONHEALTH_H
#include "Potions.h" 
#include <string>
#include <memory>
#include "Items.h"

class Player; 

class PoisonHealth: public Items, public Potions {
    public: 
        // Constructor
        PoisonHealth();
        // Destructor
        ~PoisonHealth(); 
        // apply effects of a potion to the player, returns a string that summarize what happened
        virtual std::string applyEffect(std::shared_ptr<Player> player) override;  
        // return "potion"
        virtual std::string getIdentity() override;
}; 

#endif
