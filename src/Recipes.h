#ifndef RECIPES_H
#define RECIPES_H

// Include any necessary libraries or headers here
#include <string>
#include <vector>
#include "Ingredients.h"

using namespace std;

// Declare any global constants or types here
//Enum of values of the difficulty levels
enum Level {
    None = 0,
    Easy = 1,
    Medium = 2,
    Hard = 3
};

// Declare function prototypes here
class Recipes {
    public:
    //default constructor
    Recipes();

    //defined constructor
    Recipes(string nm, string ser, string desc, vector<Ingredients>, string ins, int t, enum Level lv);

    ~Recipes();

    string getName();

    string getSeries();

    string getDescription();

    vector<Ingredients> getIngredients();

    vector<string> getIngredientsNames();

    string getInstructions();

    int getTime();

    enum Level getDifficulty();

    string toString();

    string toStringShort();

    private:
    /*Private data fields*/
    string name;
    string series;
    string description;
    vector<Ingredients> ingredients;
    string ingredients_str;
    vector<string> ingredient_names;
    string instructions;
    int time;
    enum Level difficulty;
};

#endif // RECIPES_H