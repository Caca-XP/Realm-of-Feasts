#include <iostream>
#include <string>
#include "Recipes.h" // Include the header file that contains the definition of the 'Recipes' class
using namespace std;

/* Support Class representing a singular recipe*/ 
    int main(){
        return 0;
    }

    /*Default Constructor */
    Recipes::Recipes(){
        name = "";
        series = "";
        description = "";
        ingredients = "";
        instructions = "";
        time = "";
        difficulty = "";
    };

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
    Recipes::~Recipes() {
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
    
