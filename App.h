#ifndef APP_H
#define APP_H

//necessary libraries
# include <iostream>
# include <string>
# include <fstream>
# include <array>
# include <sstream>
# include <iterator>
# include <algorithm>
# include <cstdlib>
# include <vector>

using namespace std;

/* Vector of the recipes, declared based on number of recipes in the database
*/
vector<Recipes> allRecipes;
int timeFilter = 0; // 0 for none, 1 for less than 30 minutes, 2 for 30 to 60 minutes, 3 for more than 60 minutes
int difficultyFilter = 0; // 0 for none, 1 for easy, 2 for medium, 3 for hard
int sortFilter = 0; // 0 for none, 1 for difficulty, 2 for reverse difficulty, 3 for time, 4 for reverse time

vector<string> allSeries;

/**
 * Function to process the ingredients string
 * Splits the ingredients string by commas and then by *
 * @param ingred the ingredients string
 * @return vector of Ingredients objects
 */
vector<Ingredients> process_ingred(string ingred);
/**
 * Function to process the instructions string
 * Replaces || with new line
 * @param instruct the instructions string
 * @return the processed instructions string
 */
static string process_instructions(string instruct);

/**
 * Function to process the time string
 * Converts the time string to an integer
 * @param time_str the time string
 * @return the time as an integer
 */
static int process_time(string time_str);

//Enum of values of the difficulty levels
Level process_difficulty(string difficulty_str);


/**
 * Function to read the data from the file and initialise the allRecipes array
 * Creates a new Recipes object for each recipe and adds it to the allRecipes array
 * @param fileName the name of the file to read the data from
*/
static void setup(string fileName);

/** 
 * Function to display recipes specified in the param
 * @param array of recipes
 */
static void display(vector<Recipes> recipes, bool isShort);

/** 
 * Function to sort the recipes by difficulty
 * @param a recipe a
 * @param b recipe b
 * @return true if a is less difficult than b
*/
static bool sortByDifficulty(Recipes a, Recipes b);

/** 
 * Function to sort the recipes by time
 * @param a recipe a
 * @param b recipe b
 * @return true if a takes less time than b
*/
static bool sortByTime(Recipes a, Recipes b);

/** 
 * Function to apply the settings set by the user
 * Filters the recipes based on the filters set
 * @param currentRecipes the recipes to filter
 * @return vector of recipes containing the recipes that pass the filters
*/
static vector<Recipes> applySetting(vector<Recipes> currentRecipes);

/**
 * Function to print the settings set by the user
*/
static void printSettings();

/**
 * Function to set settings for the recipes
 * User can set filters for difficulty and time
 * User can set sorting for the recipes
*/
static void setSettings();


/**
 * Function that displays a random recipe within the allRecipes array
*/
static void random();

/**
 * Function to search the recipes array by specific name
 * Prints out recipes with the searched string in its name
 * @return vector of recipes containing the instance of recipes that contain the searched string
*/
static vector<Recipes> searchByName();

/** 
 * Function that searches the array of recipes by ingredient(s) separated by commas
 * ingredient(s) will be inputed by the user by typing
 * Displays recipes that contains all of the specified ingredient(s)
 * @return vector of recipes containing recipes that contain the ingredient(s)
*/
static vector<Recipes> searchByIngredient();

/** 
 * Function to filter the recipes by series
 * Displays recipes that are in the specified series
 * @return vector of recipes containing recipes that are in the specified series
*/
static vector<Recipes> searchBySeries();



/***************************************************************************************************************************************
 *          Options and main                                                                                                           *
****************************************************************************************************************************************/

/**
 * Function to display the options for the user
 * Takes the user input and calls the appropriate function
*/
static void options();

/** Main function to run the program
 * Calls the setup function to initialise the data
 * Calls the options function to display the options for the user
*/
int main();

#endif // APP_H