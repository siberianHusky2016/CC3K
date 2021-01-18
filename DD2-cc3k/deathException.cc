#include "deathException.h"

// Constructor
deathException::deathException( int leftOver ): leftOver{ leftOver } {}

// Return the HP leftover
int deathException::getDeath() const { return leftOver;}

