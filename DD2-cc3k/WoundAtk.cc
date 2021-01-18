#include "WoundAtk.h"
#include "Player.h"

// Constructor
WoundAtk::WoundAtk(): Items{"WA", 'P'} {}

// Destructor
WoundAtk::~WoundAtk(){}

// apply effect to the player
std::string WoundAtk::applyEffect(std::shared_ptr<Player> player){
    if (player->getName() == "Drow") {
        player->changeAtk(-5 + -5/2); 
    } else {
        player->changeAtk(-5); 
    }
    return "PC uses WA."; 
}

// return "potion"
std::string WoundAtk::getIdentity() {
    return "potion"; 
}
