#include "Cell.h"
#include "DisplayableObjects.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

// Constructor
Cell::Cell(int r, int c):r{r},c{c},DefaultObject{nullptr},Object{nullptr},_Object{nullptr}{}

// return row of cell
int Cell::getr(){
    return r;
}

// Return column of cell
int Cell::getc(){
    return c;
}

// set the DefaultObject to object
void Cell::setDefault(std::shared_ptr<DisplayableObjects> object) {
    DefaultObject = object; 
}

// set the current Object and future _Object to object
void Cell::setObject(std::shared_ptr<DisplayableObjects> object) {
    Object = object; 
    _Object = object; 
}

// Clear the Object contained in the cell
void Cell::reset() {
    Object = nullptr; 
    _Object = nullptr; 
}

// Update the Object after the newest change; 
void Cell::update(){
    Object = _Object;
}

// Return the current Object, or else return the DefaultObject
std::shared_ptr<DisplayableObjects> Cell::getObject(){
    if (Object != nullptr) {
        return Object;
    }
    return DefaultObject; 
}

// Return the Object's Type on the Floor
// If no Object return DefaultObject's Type
char Cell::getObjectType() {
    if (Object != nullptr) {
        return Object->getType();
    }
    return DefaultObject->getType(); 
}

// Check if there is an Object in the cell
bool Cell::isEmpty() {
    if (Object == nullptr) {
        return true; 
    }
    return false; 
}

// Set the this's future _Object to the other's current Object and 
// Set the other's future _Object to the this's current Object
void Cell::swap(Cell & other) {
    _Object = other.Object; 
    other._Object = Object; 
}


// See if an enemy (or items) can be in this cell; 
bool Cell::enemyCanGetOn() {
    if ((this->getObjectType() == '.') && (this->_Object == nullptr)) {
        return true; 
    }
    return false; 
}

// See if the player can get on this cell; 
bool Cell::playerCanGetOn() {
    if ((this->getObjectType() == '.' || 
        this->getObjectType() == '+' || 
        this->getObjectType() == '#' || 
        this->getObjectType() == '\\' ||
	(this->getObjectType() == 'G' && !(this->getObject()->getName() == "DragonH")))
        && (this->_Object == nullptr)){
        return true; 
    }
    return false; 
}
