#include "Halfling.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

// Constructor
Halfling::Halfling(): 
    Enemies{ "Halfling", 'L', 100, 15, 20 } {}

// Destuctor
Halfling::~Halfling() {}

// Attack Player, return result
std::string Halfling::attack(std::shared_ptr<Player> Player) {
    // Compute damage
    float defence = Player->getDef();
    float attack = this->getAtk();
    float rawDamage = ceil(100/( 100+defence ) * attack);
    int absDamage = static_cast<int>(rawDamage);
    std::string result;
    result.push_back(this->getType());

    // Random number generation
    srand((unsigned) time(0));
    int randomNumber = (rand() % 10);
    if (randomNumber < 5) absDamage = 0;

    int damage = (-1) * absDamage;

    // Apply damage
    try {
        Player->changeHP( damage );
        result = result + " deals " + std::to_string(absDamage) + " damage to PC.";
    } catch ( deathException de ) {
        result = result + " deals " + std::to_string(de.getDeath()) + " damage to PC. PC is dead.";
    }
    return result;
}


