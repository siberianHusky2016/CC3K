#ifndef NOPOTIONSTOUSE_H
#define NOPOTIONSTOUSE_H
#include "InputException.h"
#include <string>

class NoPotionsToUse: public InputException {
    public:
        void printMsg() override; // print a message explain what was wrong with the input
};

#endif
