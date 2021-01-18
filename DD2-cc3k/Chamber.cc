#include "Chamber.h"
#include "Cell.h"

Chamber::Chamber() {}
// add a reference to a cell that is in the chamber to theChamber. 
void Chamber::addCell(Cell & cell) {
    theChamber.emplace_back(cell); 
}
// return the location of the cell randomly chosen to in the chamber to allocate the new object. 
std::vector<int> Chamber::chooseTile(std::vector<int> StairwayPos) {
    int index = rand() % theChamber.size(); 
    std::vector<int> position {theChamber[index].getr(), theChamber[index].getc()}; 
    std::vector<int> result; 
    if (StairwayPos[0] == position[0] && StairwayPos[1] == position[1]) {
        theChamber.erase(theChamber.begin() + index); 
        index = rand() % theChamber.size(); 
        result.emplace_back(theChamber[index].getr()); 
        result.emplace_back(theChamber[index].getc());
    } else {
        result = position; 
    }
    theChamber.erase(theChamber.begin() + index); 
    return result; 
}

// If there are no cells left in theChamber
bool Chamber::isEmpty() {
    if (theChamber.size() == 0) {
        return true; 
    } 
    return false; 
}

