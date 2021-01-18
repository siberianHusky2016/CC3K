#ifndef RESTOREHEALTH_H
#define RESTOREHEALTH_H
#include "Potions.h" 
#include <string>
#include <memory>
#include "Items.h"

class Player; 

class RestoreHealth: public Potions, public Items {
    public: 
        // Constructor
        RestoreHealth(); 
        // Destructor
        ~RestoreHealth(); 
        // apply effects of a potion to the player, returns a string that summarize what happened
        virtual std::string applyEffect(std::shared_ptr<Player> player) override;  
        // return "potion"
        virtual std::string getIdentity() override; 
}; 

#endif
