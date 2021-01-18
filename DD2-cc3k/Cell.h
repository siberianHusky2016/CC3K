#ifndef CELL_H
#define CELL_H
#include <cstddef> // defines size_t i.e. an unsigned int
#include <iostream>
#include <vector>
#include <memory>

class DisplayableObjects; 

class Cell {
  private:
    // Add other private members if necessary
    int r; 
    int c; 
    // Floors, Doors, Passage, is to put in this. 
    std::shared_ptr<DisplayableObjects> DefaultObject; 
    std::shared_ptr<DisplayableObjects> Object; 
    std::shared_ptr<DisplayableObjects> _Object; 

  public: 
    // Constructor. 
    Cell(int r, int c); 

    // return row of cell
    int getr(); 

    // Return column of cell
    int getc(); 

    // set the DefaultObject to object
    void setDefault(std::shared_ptr<DisplayableObjects> object); 

    // set the current Object and future _Object to object
    void setObject(std::shared_ptr<DisplayableObjects> object); 

    // Resets the Object and _Object to nullptr. 
    void reset(); 

    // Change Object to _Object; 
    void update(); 

    // Observer calls this to get the object on the top of the cell.
    virtual std::shared_ptr<DisplayableObjects> getObject();

    // Return the Type of Displayable Objects. If Object == nullptr, return DefaultObject's Type. 
    char getObjectType(); 

    // Return true if the the cell does not hold a non-surrounding displayable object. 
    bool isEmpty(); 
    
    // Set the this's future _Object to the other's current Object and 
    // Set the other's future _Object to the this's current Object
    void swap(Cell & other);

    // See if an enemy (or items) can be in this cell; 
    bool enemyCanGetOn(); 

    // See if the player can get on this cell; 
    bool playerCanGetOn(); 
};

#endif
