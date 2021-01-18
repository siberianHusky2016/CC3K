#include "Surroundings.h"

// Constructor
Surroundings::Surroundings(std::string name, char type):
    DisplayableObjects{ name, type } {}

// return the Name of the Surroundings
std::string Surroundings::getIdentity(){
    return Name;
}
