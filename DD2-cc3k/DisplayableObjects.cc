#include "DisplayableObjects.h"

// Constructor
DisplayableObjects::DisplayableObjects( const std::string & Name, char Type): 
    Name{ Name }, Type{ Type } {}

DisplayableObjects::~DisplayableObjects() {} // Destructor

std::string DisplayableObjects::getName() { return Name; } // get the Name of the object

char DisplayableObjects::getType() { return Type; } // get the Character displayed on the text display

void DisplayableObjects::setName(std::string name) { Name = name; } // set the name of the object

void DisplayableObjects::setType(char type) { Type = type; } // set the displayed type of the object
