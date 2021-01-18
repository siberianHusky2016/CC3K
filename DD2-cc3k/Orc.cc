#include "Orc.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

// Constructor
Orc::Orc(): 
    Enemies{ "Orc", 'O', 180, 30, 25 } {}

// Destructor
Orc::~Orc() {}

// Attack Player, return result
std::string Orc::attack(std::shared_ptr<Player> Player) {
    // Compute damage
    float defence = Player->getDef();
    float attack = this->getAtk();
    float rawDamage = ceil(100/( 100+defence ) * attack);
    int absDamage = static_cast<int>(rawDamage);
    std::string result;
    result.push_back(this->getType());

    // Check if the target is goblin
    if (Player->getName() != "Goblin") {
        rawDamage = rawDamage * 1.5;
        absDamage = static_cast<int>(rawDamage);
    }

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



