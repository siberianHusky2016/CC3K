#include <string>

class deathException {
  private:
    int leftOver; // HP leftover before death
  public:
    // Constructor
    deathException( int leftOver );
    // Return the HP leftover
    int getDeath() const; 
};

