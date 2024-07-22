#include <iostream>
#include <string>
#include "Recipes.h"
using namespace std;

/* Support Class representing a singular recipe
*/

class Recipes {
private:
    /*Private data fields*/
    string name;
    string series;
    string description;
    string ingredients;
    string instructions;
    string time;
    string difficulty;

public:
    /*Default Constructor */
    Recipes::Recipes(){};

    /*Defined Constructor*/
    Recipes::Recipes(string nm, string ser, string desc, string ing, string ins, string t, string lv) {
        name = nm;
        series = ser;
        description = desc;
        ingredients = ing;
        instructions = ins;
        time = t;
        difficulty = lv;

        
    }

    /*Destructor code (idk what this is for)*/
    ~Recipes() {
        // Destructor code here
    }

    /* Accessor function to get the name of the recipe
    */
    string Recipes::getName() {
        return name;
    }

    /* Accessor function to get the description of the recipe
    */
    string Recipes::getDescription() {
        return description;
    }

    /* Accessor function to get the ingredients of the recipe
    */
    string Recipes::getIngredients() {
        return ingredients;
    }

    /* Accessor function to get the instructions of the recipe
    */
    string Recipes::getInstructions() {
        return instructions;
    }

    /* Accessor function to get the time of the recipe
    */
    string Recipes::getTime() {
        return time;
    }

    /* Accessor function to get the difficulty of the recipe
    */
    string Recipes::getDifficulty() {
        return difficulty;
    }
    
};