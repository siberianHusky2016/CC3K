#include "BoostDef.h"
#include "Player.h"

// Constructor
BoostDef::BoostDef(): Items{"BD", 'P'} {} 

// Destructor
BoostDef::~BoostDef(){}

// Return the effect, change the Player Characteristics
std::string BoostDef::applyEffect(std::shared_ptr<Player> player){
    if (player->getName() == "Drow") {
        player->changeDef(5 + 5/2); 
    } else {
        player->changeDef(5); 
    }
    return "PC uses BD.";
}

// Get the identity of potion
std::string BoostDef::getIdentity() {
    return "potion"; 
}
