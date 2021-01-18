#ifndef CHAMBER_H
#define CHAMBER_H
#include <iostream>
#include <vector>
#include <cstdlib>

class Cell; 

class Chamber {
    private: 
        std::vector<Cell> theChamber; 
    public: 
        // Constructor
        Chamber();
        // add a reference to a cell that is in the chamber to theChamber. 
        void addCell(Cell & cell);
        // return the location of the cell randomly chosen to in the chamber to allocate the new object. 
        std::vector<int> chooseTile(std::vector<int> StairwayPos); 
        // return the size of theChamber
        int size() {return theChamber.size();}
        // return the size of theChamber
        bool isEmpty();
}; 


#endif
