#include "RestoreHealth.h"
#include "Player.h"

// Constructor
RestoreHealth::RestoreHealth(): Items{"RH", 'P'} {} 

// Destructor
RestoreHealth::~RestoreHealth(){}

// apply effect to the player
std::string RestoreHealth::applyEffect(std::shared_ptr<Player> player){
    if (player->getName() == "Drow") {
        player->changeHP(15); 
    } else {
        player->changeHP(10); 
    }
    return "PC uses RH.";
}

// return "potion"
std::string RestoreHealth::getIdentity() {
    return "potion"; 
}
