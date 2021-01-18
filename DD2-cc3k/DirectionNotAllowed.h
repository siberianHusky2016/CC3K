#ifndef DIRECTIONNOTALLOWED_H
#define DIRECTIONNOTALLOWED_H
#include "InputException.h"
#include <string>

class DirectionNotAllowed: public InputException {
    public:
        void printMsg() override; // Print a message explain the error
};

#endif
