#ifndef FLOOR_H
#define FLOOR_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <cstdlib>
#include "Cell.h"
#include "Chamber.h"
#include <map>

class Cell; 
class Chamber; 

// Grid is initially empty. Sets up a TextDisplay observer when init() is called
// and the grid is initialized with cell objects.
class Floor {

    std::vector<std::vector<Cell>> floor; // Grid of Cells,the Floor
    std::vector<int> PlayerPos; // Player postion; [r, c]
    std::vector<int> StairwayPos; // Stairway postion; [r, c]
    std::vector<Chamber> Chambers; // Chambers
    int level; // the (level)th floor
    std::map<std::string, std::string> compass{ // map of abbrev direction to actual direction name
      {"no", "North"},
      {"ne", "Northeast"},
      {"ea", "East"},
      {"se", "Southeast"},
      {"so", "South"}, 
      {"sw", "Southwest"},
      {"we", "West"},
      {"nw", "Northwest"},
    };

  public: 
    // Constructor 
    Floor();
    
    // Fill cells as empty floor plan
    void set_Floor(std::string character, int floor); 
    
    // Fill cells as given floor plan
    void set_Floor(std::string character, std::string file_txt, int floor); 

    // Set the chambers by adding references of Cells to each Chamber in Chambers. 
    void createChamber(); 

    // Return a randomly chosen index for Chambers
    int chooseChamber(); 
    
    // Get a Chamber from Chambers by index
    Chamber getChamber(int index); 

    // Generate Player Character and Stairway on this floor, takes in the name of the character
    // Player Character and Stairway cannot be in the same Chamber
    // Modify the PlayerPos and StairwayPos accordingly. 
    void generatePlayerandStairway(std::string character); 

    // generate all Teasure and Potions on the floor
    void generateItems(); 

    // generate all Enemies on the floor
    void generateEnemies(); 

    // Move the player in the direction specified and move all the enemies in a turn; 
    std::string step(std::string playerDirection, bool enemies_can_move); 

    // Return the cell coordinate with respect to the direction of current player position. 
    // Throw error if out of bounds. 
    std::vector<int> DirectionLocation(std::string direction); 
    
    // Player use the potion in the desired location
    // return a string that explains what happend
    std::string usePotion(std::string playerDirection); 

    // Attack the enemy in the direction given; 
    // return a string that explains what happened. 
    std::string attackEnemies(std::string PlayerDirection); 

    // Enemy Autoattack player in within range after movements
    std::string EnemySearchForAtk(); 

    // Update each cell after movements
    void update(); 

    // Check if a player has reached the stairs and should go to the next level
    bool checkNextFloor(); 

    // Check if player is on the stair
    bool playeronstair();

    // Copy the current player health to the new floor, discard potion effects on atk and def
    void copyPlayerHealth(Floor & other); 

    // Friend Function; print the floor information.
    friend std::ostream & operator<<( std::ostream & out, Floor & f );
};

// Uses the TextDisplay to output the grid information.
std::ostream & operator<<( std::ostream & out, Floor & f );

#endif

