#include "Player.h"
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Merchant.h"

// Constructor
Player::Player( const std::string & Name, char Type, int HP, int Atk, int Def, int Gold, int maxHP ):
    Characters{ Name, Type, HP, Atk, Def }, 
    Gold{ Gold },
    maxHP{ maxHP } {}

// Destructor
Player::~Player() {}

// Return the amount of gold the player has
int Player::getGold() { return Gold; }

// Get the maximum HP player can have
int Player::getMaxHP() { return maxHP; }

// Change the amount of gold the player has by delta
void Player::changeGold(int delta) {
    // std::cout << "changing gold" << std::endl; 
    Gold = Gold + delta; 
}

// change the hp based on the delta
void Player::changeHP(int delta) {
    int current = this->getHP();
    int after = current + delta;
    if (after <= 0) {
        // dead
        // std::cout << "Declared Dead!" << std::endl;
        this->HP = 0;
        throw deathException{ current };
    } else if (after >= maxHP) { 
        // cap 
        this->HP = maxHP;
    } else {
        this->HP = after;
    }
}

// Attack an enemy, return result
std::string Player::attack(std::shared_ptr<Enemies> enemy) {
    float defence = enemy->getDef();
    float attack = this->getAtk();
    float rawDamage = ceil(100/( 100+defence ) * attack);
    int absDamage = static_cast<int>(rawDamage);
    std::string result;

    // Random number generation
    srand((unsigned) time(0));
    int randomNumber = (rand() % 10);
    if (randomNumber < 5 && enemy->getName() == "Halfling") absDamage = 0;
    if (enemy->getName() == "Merchant") {
        std::shared_ptr<Merchant> m = std::dynamic_pointer_cast<Merchant>(enemy); 
        m->setHostile();
    }
    int damage = (-1) * absDamage;

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

    return result;
}

// Return "player"
std::string Player::getIdentity(){ return "player"; }

