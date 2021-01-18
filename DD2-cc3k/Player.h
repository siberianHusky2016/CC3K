#ifndef PLAYER_H
#define PLAYER_H
#include "Characters.h" 
#include "deathException.h"
#include "Enemies.h"
#include <memory> 
#include <string>

class Enemies; 

class Player: public Characters {
    private: 
        int Gold; 
        int maxHP; 
    public: 
        // Constructor
        Player( const std::string & Name, char Type, int HP, int Atk, int Def, int Gold, int maxHP );
        // Destructor
        virtual ~Player();
        // called when attacking an enemy, return a displayable texts that summarize what happened
        virtual std::string attack(std::shared_ptr<Enemies> enemy); 
        int getGold();  // gets the current Gold
        int getMaxHP(); // gets the maxHP
        void changeGold(int delta); // changes Gold by delta
        // overrides changeHP so HP cannot be more than maxHP
        virtual void changeHP(int delta) override; 
        // Return "player"
        virtual std::string getIdentity() override;
}; 

#endif

