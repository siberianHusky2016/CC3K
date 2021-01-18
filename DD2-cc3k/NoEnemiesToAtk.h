#ifndef NOENEMIESTOATK_H
#define NOENEMIESTOATK_H
#include "InputException.h"
#include <string>

class NoEnemiesToAtk: public InputException {
    public:
        void printMsg() override; // print a message explain what was wrong with the input
};

#endif
