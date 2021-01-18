#include "Dragon.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

// Constructor
Dragon::Dragon(): 
    Enemies{ "Dragon", 'D', 150, 20, 20 } {}

// Destructor
Dragon::~Dragon() {}

// Attack the Player, return result
std::string Dragon::attack(std::shared_ptr<Player> Player) {
    // Compute damage
    float defence = Player->getDef();
    float attack = this->getAtk();
    float rawDamage = ceil(100/( 100+defence ) * attack);
    int absDamage = static_cast<int>(rawDamage);
    int damage = (-1) * absDamage;
    std::string result;
    result.push_back(this->getType());

    // Random number generation
    srand((unsigned) time(0));
    int randomNumber = (rand() % 10);
    if (randomNumber < 5) damage = 0;

    // Apply damage
    try {
        Player->changeHP( damage );
        result = result + " deals " + std::to_string(absDamage) + " damage to PC.";
    } catch ( deathException de ) {
        result = result + " deals " + std::to_string(de.getDeath()) + " damage to PC. PC is dead.";
    }
    return result;
}

