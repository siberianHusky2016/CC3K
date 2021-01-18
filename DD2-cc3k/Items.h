#ifndef ITEMS_H
#define ITEMS_H
#include "DisplayableObjects.h" 
#include <string>

class Items: public DisplayableObjects {
    public:
        Items(const std::string & Name, char Type); // Constructor
        ~Items(); // Destructor
}; 

#endif
