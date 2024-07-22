#include <iostream>
#include <string>
using namespace std;

class Recipes {
private:
    string name;
    string description;
    string ingredients;
    string instructions;
    string time;
    string difficulty;

public:
    Recipes(string nm, string desc, string ing, string ins, string t, string lv) {
        name = nm;
        description = desc;
        ingredients = ing;
        instructions = ins;
        time = t;
        difficulty = lv;

        
    }

    ~Recipes() {
        // Destructor code here
    }

    /* Accessor function to get the name of the recipe
    */
    string getName() {
        return name;
    }

    /* Accessor function to get the description of the recipe
    */
    string getDescription() {
        return description;
    }

    /* Accessor function to get the ingredients of the recipe
    */
    string getIngredients() {
        return ingredients;
    }

    /* Accessor function to get the instructions of the recipe
    */
    string getInstructions() {
        return instructions;
    }

    /* Accessor function to get the time of the recipe
    */
    string getTime() {
        return time;
    }

    /* Accessor function to get the difficulty of the recipe
    */
    string getDifficulty() {
        return difficulty;
    }
    
};