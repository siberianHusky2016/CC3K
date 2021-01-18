#ifndef DISPLAYABLEOBJECTS_H
#define DISPLAYABLEOBJECTS_H
#include <string>

class DisplayableObjects {
    protected: 
        std::string Name; // Name of the object, all lower case
        char Type; // Character displayed on the text display
    public: 
        DisplayableObjects( const std::string & Name, char Type); // Constructor
        virtual ~DisplayableObjects(); // Destructor
        std::string getName(); // get the Name of the object
        char getType(); // get the displayed type of the object
        virtual std::string getIdentity()=0; // get the identity of the object
        void setName(std::string name); // set the name of the object
        void setType(char type); // set the displayed type of the object
}; 

#endif

