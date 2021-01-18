#include "Enemies.h"

// Constructor
Enemies::Enemies( const std::string & Name, char Type, int HP, int Atk, int Def):
    Characters{ Name, Type, HP, Atk, Def } {}

// Destructor
Enemies::~Enemies() {} 

// change the hp based on the delta
void Enemies::changeHP(int delta) {
    int current = this->getHP();
    int after = current + delta;
    if (after <= 0) {
        // dead
        // std::cout << "Declared Dead!" << std::endl;
        this->HP = 0;
        throw deathException{ current };
    } else {
        this->HP = after;
    }
}

// return "enemy"
std::string Enemies::getIdentity(){ return "enemy"; }

