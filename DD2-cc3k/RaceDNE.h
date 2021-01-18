#ifndef RACEDNE_H
#define RACEDNE_H
#include "InputException.h"
#include <string>

class RaceDNE: public InputException {
    public:
        void printMsg() override; // print a message explain what was wrong with the input
};

#endif
