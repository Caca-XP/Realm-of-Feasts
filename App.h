/*! @file
*@brief App.h contains the declarations of the functions used in the main program
*@authors Natasha, Nadia and Bernice
*/

#pragma once
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
#include <chrono> // Required for std::chrono::seconds
#include <thread> // Required for std::this_thread::sleep_for


# include "Recipes.h" // Include the header file that contains the definition of the 'Recipes' class
# include "Ingredients.h" // Include the header file that contains the definition of the 'Ingredients' class
# include "Support.h" // Include the header file that contains the definition of the 'Ingredients' class
#include <chrono> // Required for std::chrono::seconds
#include <thread> // Required for std::this_thread::sleep_for


using namespace std;


vector<Recipes> allRecipes;
int timeFilter = 0; // 0 for none, 1 for less than 30 minutes, 2 for 30 to 60 minutes, 3 for more than 60 minutes
int difficultyFilter = 0; // 0 for none, 1 for easy, 2 for medium, 3 for hard
int sortFilter = 0; // 0 for none, 1 for difficulty, 2 for reverse difficulty, 3 for time, 4 for reverse time
vector<string> allSeries;

/*!
 * @brief Function to process the ingredients string
 * @details Splits the ingredients string by commas and then by *
 * @param ingred the ingredients string
 * @return vector of Ingredients objects
 */
vector<Ingredients> process_ingred(string ingred);

/*!
 * @brief Function to process the instructions string
 * @details Replaces || with new line
 * @param instruct the instructions string
 * @return the processed instructions string
 */
static string process_instructions(const string& instruct);

/*!
 * @brief Function to process the time string
 * @details Converts the time string to an integer
 * @param time_str the time string
 * @return the time as an integer
 */
static int process_time(const string& time_str);

/*!
*@brief Converts a difficulty string into its corresponding enum Level value.
*@param difficulty_str The string to convert.
*@return The corresponding enum Level value.
*/
Level process_difficulty(const string& difficulty_str);


/*!
 * @brief Function to read the data from the file and initialise the allRecipes array
 * @details Creates a new Recipes object for each recipe and adds it to the allRecipes array
 * @param fileName the name of the file to read the data from
*/
static void setup(string fileName);

/*!
 * @brief Function to display recipes specified in the param
 * @param array of recipes
 */
static void display(vector<Recipes> recipes, bool isShort);

/*!
 * @brief Function to sort the recipes by difficulty
 * @param a recipe a
 * @param b recipe b
 * @return true if a is less difficult than b
*/
static bool sortByDifficulty(Recipes a, Recipes b);

/*!
 *@brief Function to sort the recipes by time
 * @param a recipe a
 * @param b recipe b
 * @return true if a takes less time than b
*/
static bool sortByTime(Recipes a, Recipes b);

/*!
 *@brief Function to apply the settings set by the user
 *@details Filters the recipes based on the filters set
 * @param currentRecipes the recipes to filter
 * @return vector of recipes containing the recipes that pass the filters
*/
static vector<Recipes> applySetting(vector<Recipes> currentRecipes);

/*!
 *@brief Function to print the settings set by the user
*/
static void printSettings();

/*!
 * @brief Function to set settings for the recipes
 * @details User can set filters for difficulty and time
 * User can set sorting for the recipes
*/
static void setSettings();


/*!
 * @brief Function that displays a random recipe within the allRecipes array
*/
static void random();

/*!
 * @brief Function to search the recipes array by specific name
 * @details Prints out recipes with the searched string in its name
 * @return vector of recipes containing the instance of recipes that contain the searched string
*/
static vector<Recipes> searchByName();

/*!
 * @brief Function that searches the array of recipes by ingredient(s) separated by commas
 * ingredient(s) will be inputed by the user by typing
 * @details Displays recipes that contains all of the specified ingredient(s)
 * @return vector of recipes containing recipes that contain the ingredient(s)
*/
static vector<Recipes> searchByIngredient();

/*!
 * @brief Function to filter the recipes by series
 * @details Displays recipes that are in the specified series
 * @return vector of recipes containing recipes that are in the specified series
*/
static vector<Recipes> searchBySeries();



/***************************************************************************************************************************************
 *          Options and main                                                                                                           *
****************************************************************************************************************************************/

/**
 *@brief Function to display the options for the user
 *@details Takes the user input and calls the appropriate function
*/
static void options();

/** 
 * @brief Main function to run the program
 * @details Calls the setup function to initialise the data
 * Calls the options function to display the options for the user
*/
int main();

#endif // APP_H