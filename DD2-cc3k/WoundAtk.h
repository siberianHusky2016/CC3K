#ifndef WOUNDATK_H
#define WOUNDATK_H
#include "Potions.h" 
#include <string>
#include <memory>
#include "Items.h"

class Player; 

class WoundAtk: public Potions, public Items {
    public: 
        // Constructor
        WoundAtk(); 
        // Destructor
        ~WoundAtk(); 
        // apply effects of a potion to the player, returns a string that summarize what happened
        virtual std::string applyEffect(std::shared_ptr<Player> player) override;  
        // return "potion"
        virtual std::string getIdentity() override; 
}; 

#endif
