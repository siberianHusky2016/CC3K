#ifndef ENEMIES_H
#define ENEMIES_H
#include "Characters.h"
#include "Player.h"
#include <memory>
#include <string>

class Player; 

class Enemies: public Characters {
    public: 
        Enemies( const std::string & Name, char Type, int HP, int Atk, int Def); // Constructor
        virtual ~Enemies(); // Destructor
        // called when attacking the player, return a displayable texts that summarize what happened
        virtual std::string attack(std::shared_ptr<Player> player) = 0; // attack a player character
        virtual void changeHP(int delta) override; // change the hp based on the delta 
        virtual std::string getIdentity() override; // return "enemy"
}; 

#endif
