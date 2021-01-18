#ifndef SURROUNDINGS_H
#define SURROUNDINGS_H
#include "DisplayableObjects.h" 
#include <string>

class Surroundings: public DisplayableObjects {
    public: 
        Surroundings(std::string name, char type); //construct a Surrounding object
        virtual std::string getIdentity() override; // return the Name of the Surroundings
}; 

#endif
