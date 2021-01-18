#include "PoisonHealth.h"
#include "Player.h"

// Constructor
PoisonHealth::PoisonHealth(): Items{"PH", 'P'} {} 

// Destructor
PoisonHealth::~PoisonHealth(){}

// apply effect to the player
std::string PoisonHealth::applyEffect(std::shared_ptr<Player> player){
    if (player->getName() == "Drow") {
        player->changeHP(-15); 
    } else {
        player->changeHP(-10); 
    }
    return "PC uses PH.";
}

// return "potion"
std::string PoisonHealth::getIdentity() {
    return "potion"; 
}
