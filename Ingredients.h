#ifndef Ingredients_H
#define Ingredients_H

// Include any necessary libraries or headers here
#include <string>

using namespace std;

// Declare any global constants or types here

// Declare function prototypes here
class Ingredients {
    public:
    //default constructor
    Ingredients();

    //defined constructor
    Ingredients(double q, string un, string nm);

    ~Ingredients();

    string getName();

    string getUnit();

    double getQuantity();

    string toString();

    private:
    /*Private data fields*/
    string name;
    string unit;
    double quantity;
};

#endif // Ingredients_H