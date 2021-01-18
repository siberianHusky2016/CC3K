#include "WoundDef.h"
#include "Player.h"

// Constructor
WoundDef::WoundDef() : Items{"WD", 'P'} {}

// Destructor
WoundDef::~WoundDef(){}

// apply effect to the player
std::string WoundDef::applyEffect(std::shared_ptr<Player> player){
    if (player->getName() == "Drow") {
        player->changeDef(-5 + -5/2); 
    } else {
        player->changeDef(-5); 
    }
    return "PC uses WD."; 
}

// return "potion"
std::string WoundDef::getIdentity() {
    return "potion"; 
}
