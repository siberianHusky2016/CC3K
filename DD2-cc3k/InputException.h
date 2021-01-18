#ifndef INPUTEXCEPTION_H
#define INPUTEXCEPTION_H
#include <string>

class InputException {
  public:
    virtual void printMsg() = 0; // print a message explain what was wrong with the input
};

#endif

