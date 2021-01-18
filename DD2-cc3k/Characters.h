#ifndef CHARACTERS_H
#define CHARACTERS_H
#include "DisplayableObjects.h"

class Characters: public DisplayableObjects {
    protected: 
        int HP;     //HP of character
        int Atk;    //Atk of character
        int Def;    //Def of character
    public: 
        Characters( const std::string & Name, char Type, int HP, int Atk, int Def );
        virtual ~Characters();
        int getHP();    //gets the current HP
        int getAtk();   //gets the current Atk
        int getDef();   //gets the current Def
        virtual void changeHP(int delta) = 0;   //changes the HP by delta
        void changeAtk(int delta);          //changes the Atk by delta
        void changeDef(int delta);          //changes the Def by delta
}; 

#endif

