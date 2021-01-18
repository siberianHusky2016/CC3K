#include "Treasures.h"

// Constructor
Treasures::Treasures(std::string name):
    Items{ name, 'G' }{
        if (name == "Small") {
            ID = "Collectible";
            size = 1; 
        } else if (name == "Normal") {
            ID = "Collectible";
            size = 2; 
        } else if (name == "MerchantH") {
            ID = "Collectible";
            size = 4; 
        } else if (name == "DragonH") {
            ID = "Uncollectible";
            size = 6; 
        }
}

// Destructor
Treasures::~Treasures(){}

//return the size of the Treasure
int Treasures::getSize() {
    return this->size; 
}

// Return if the treasure is "Collectible" or "Uncollectible"
std::string Treasures::getIdentity(){
    return ID;
}

// Set the Identity to "Collectible" or "Uncollectible"
void Treasures::setIdentity(std::string newIdentity){
    ID = newIdentity;
}

