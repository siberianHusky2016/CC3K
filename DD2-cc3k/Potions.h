#ifndef POTIONS_H
#define POTIONS_H
#include "DisplayableObjects.h" 
#include <string>
#include <memory>

class Player; 

// Strategy pattern Potions interface
class Potions{
    public: 
        //apply effects of a potion to the player, returns a string that summarize what happened
        virtual std::string applyEffect(std::shared_ptr<Player> player)=0;  
}; 

#endif
