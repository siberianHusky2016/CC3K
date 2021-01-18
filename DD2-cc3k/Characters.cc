#include "Characters.h"

// Constructor
Characters::Characters( const std::string & Name, char Type, int HP, int Atk, int Def ): 
    DisplayableObjects{ Name, Type }, 
    HP{ HP }, 
    Atk{ Atk }, 
    Def{ Def } {}

// Destructor
Characters::~Characters(){}

// Return Character HP
int Characters::getHP() { return HP; }

// Return Atk value; 
int Characters::getAtk() { return Atk; }

// Return Def value; 
int Characters::getDef() { return Def; }

// Change the Atk value by delta; 
void Characters::changeAtk(int delta) { this->Atk = this->Atk + delta; }

// Change the Def value by delta; 
void Characters::changeDef(int delta) { this->Def = this->Def + delta; }

