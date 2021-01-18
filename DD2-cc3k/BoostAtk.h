#ifndef BOOSTATK_H
#define BOOSTATK_H
#include "Potions.h" 
#include <string>
#include <memory>
#include "Items.h"

class Player; 

class BoostAtk: public Potions, public Items {
    public: 
        // Constructor
        BoostAtk(); 
        // Destructor
        ~BoostAtk(); 
        // Apply effects of a potion to the player, returns a string that summarize what happened
        virtual std::string applyEffect(std::shared_ptr<Player> player) override;  
        // Get the identity of potion
        virtual std::string getIdentity() override; 
}; 

#endif
