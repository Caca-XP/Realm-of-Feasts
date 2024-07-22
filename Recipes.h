#ifndef RECIPES_H
#define RECIPES_H

// Include any necessary libraries or headers here
#include <string>
using namespace std;

// Declare any global constants or types here

// Declare function prototypes here
class Recipes {
    public:
    //default constructor
    Recipes();

    //defined constructor
    Recipes(string nm, string ser, string desc, string ing, string ins, int t, enum Level lv);

    ~Recipes();

    string getName();

    string getDescription();

    string getIngredients();

    string getInstructions();

    int getTime();

    enum Level getDifficulty();

    string toString();

    private:
    /*Private data fields*/
    string name;
    string series;
    string description;
    string ingredients;
    string instructions;
    int time;
    enum Level difficulty;
};

#endif // RECIPES_H