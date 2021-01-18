#include "Vampire.h"
#include <cmath>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Merchant.h"


// Constructor
Vampire::Vampire(): 
    Player{ "Vampire", '@', 50, 25, 25, 0, 2147483647 } {}

// Destructor
Vampire::~Vampire() {}

// Attack an enemy, return result
// implemented special abilities of Vampire
std::string Vampire::attack(std::shared_ptr<Enemies> enemy) {
    float defence = enemy->getDef();
    float attack = this->getAtk();
    float rawDamage = ceil(100/( 100+defence ) * attack);
    int absDamage = static_cast<int>(rawDamage);
    std::string result;

    // Random number generation
    srand((unsigned) time(0));
    int randomNumber = (rand() % 10);
    if (randomNumber < 5 && enemy->getName() == "Halfling") absDamage = 0;
    int damage = (-1) * absDamage;
    if (enemy->getName() == "Merchant") {
        std::shared_ptr<Merchant> m = std::dynamic_pointer_cast<Merchant>(enemy); 
        m->setHostile();
    }

    try {
        enemy->changeHP( damage );
        result = "PC deals " + std::to_string(absDamage) + " damage to " + enemy->getType() 
                + " (" + std::to_string(enemy->getHP()) + " HP). ";
    } catch ( deathException de ) {
        if (enemy->getName() == "Human") {
            this->changeGold(2);
            // drop another 2 gold
        } else if ( enemy->getName() == "Merchant") {
            this->changeGold(4);
        } else if ( enemy->getName() != "Dragon") { 
            int randomGold = (rand() % 2);
            if (randomGold == 0) this->changeGold(1);
            else this->changeGold(2);
        } 
        result = "PC deals " + std::to_string(de.getDeath()) + " damage to " + enemy->getType() + ". "
                + enemy->getType() + " has been slained.";
    }
    if (enemy->getName() == "Dwarf"){
        this->changeHP(-5);
    } else {
        this->changeHP(5);
    }
    
    return result;
}

