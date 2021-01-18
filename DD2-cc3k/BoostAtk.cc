#include "BoostAtk.h"
#include "Player.h"

// Constructor
BoostAtk::BoostAtk(): Items{"BA", 'P'} {} 

// Destructor
BoostAtk::~BoostAtk(){}

// Return the effect, change the Player Characteristics
std::string BoostAtk::applyEffect(std::shared_ptr<Player> player){
    if (player->getName() == "Drow") {
        player->changeAtk(5 + 5/2); 
    } else {
        player->changeAtk(5); 
    }
    return "PC uses BA."; 
}

// Get the identity of potion
std::string BoostAtk::getIdentity() {
    return "potion"; 
}
