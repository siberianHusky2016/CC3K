#ifndef Merchant_H
#define Merchant_H
#include "Enemies.h"
#include <memory>
#include <string>

class Player; 

class Merchant: public Enemies {
    private: 
        static bool IsHostile; 
    public: 
        Merchant(); //constructs a Merchant character
        ~Merchant();
        // called when a merchant is attacked by the player, return a displayable texts that summarize what happened
        void setHostile(); 
        void setFriendly(); 
        bool getHostile(); 
        // called when attacking the player, return a displayable texts that summarize what happened
        virtual std::string attack(std::shared_ptr<Player> player) override; 
}; 

#endif
