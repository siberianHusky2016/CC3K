#ifndef TREASURES_H
#define TREASURES_H
#include <string>
#include "Items.h"

class Treasures: public Items {
    private: 
        std::string ID; // "Collectible" or "Uncollectible"
        int size; 
    public: 
        //Constructs a Treasure, deppends on the Name of Tresure
        //Type = 'G'
        //"Small" is size 1
        //"Normal" is size 2
        //"MerchantH" is size 4
        //"DragonH" is size 6
        // Constructor
        Treasures(std::string name); 
        // Destructor
        ~Treasures();
        //return the size of the Treasure
        int getSize(); 
        // Return if the treasure is "Collectible" or "Uncollectible"
        virtual std::string getIdentity() override;
        // Set the Identity to either "Collectible" or "Uncollectible"
        void setIdentity(std::string newIdentity);
}; 

#endif
