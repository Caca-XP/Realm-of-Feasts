/*!
   @file
   @brief Header file for Support.cpp
   @author Natasha and Nadia 
*/
#pragma once
#ifndef SUPPORT_H
#define SUPPORT_H

//Header file for Support.cpp
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
# include "RealmOfRecipes.h" // Include the header file that contains the definition of the 'RealmOfRecipes' class
# define NOMINMAX
# include <windows.h>


using namespace std;




/*!
 *@brief Function to split a string into a vector of strings
 *@brief Splits the string by the delimiter
 *
 * @param str the string to split
 * @param delimiter the delimiter to split the string by
 * @param lowercase whether to convert the string to lowercase
 * @return vector of strings
 */
vector<string> split_string(string str, string delimiter, bool lowercase);

/*!
*@brief Function to quit the program
*@details Terminates the program's execution
*/
void quit();

/*! Function to print goodbye
*/
void printGoodbye();

/*!
*@brief Function to replace comma space to comma
*@details Remove empty spaces
*@param str the string to replace
*@param from the string to replace
*@param to the substring to replace with
*@return the modified string with replacement made 
*/
string replaceAll(string str, string from, string to);

/*!
*@brief Function to read the whole line of user input
*@param ignore If true, ignores the newline character left in the input stream from previous input.
*@return the user input (the whole line of input as string)
 */
string readLine(bool ignore);

/*!
 * @brief Function to set the color of the text in the console
 * @param color the color to set
 */
void setColor(int color);

/*!
 * @brief Function to get the current color of the text in the console
 * @return the current color of the text in the console as an integer
 */
int getCurrentColor();

/*!
 * @brief Function to restrict each line length
 * @param str the string to restrict
 * @param length the length to restrict the string to
 * @param divider the divider for next lines
 * @param space the space to add
 * @return the restricted string
 */
string restrictLineLength(string str, int length, char divider, int space);

/*!
 * @brief Function to process the ingredients string
 * @details Splits the ingredients string by commas and then by *
 * @param ingred the ingredients string
 * @return vector of Ingredients objects
 */
vector<Ingredients> process_ingred(const string& ingred);

/*!
 * @brief Function to process the instructions string
 * @details Replaces || with new line
 * @param instruct the instructions string
 * @return the processed instructions string
 */
 string process_instructions(const string& instruct);

/*!
 * @brief Function to process the time string
 * @details Converts the time string to an integer
 * @param time_str the time string
 * @return the time as an integer
 */
 int process_time(const string& time_str);

/*!
*@brief Converts a difficulty string into its corresponding enum Level value.
*@param difficulty_str The string to convert.
*@return The corresponding enum Level value.
*/
Level process_difficulty(string difficulty_str);

/*!
 * @brief Function to read the data from the file and initialise the allRecipes array
 * @details Creates a new Recipes object for each recipe and adds it to the allRecipes array
 * @param fileName the name of the file to read the data from
*/
 void setup(string fileName, RealmOfRecipes& app);

/*!
 * @brief Function to display recipes specified in the param
 * @param array of recipes
 */
 void display(vector<Recipes> recipes, bool isShort);

/*!
 * @brief Function to sort the recipes by difficulty
 * @param a recipe a
 * @param b recipe b
 * @return true if a is less difficult than b
*/
 bool sortByDifficulty(Recipes a, Recipes b);

/*!
 *@brief Function to sort the recipes by time
 * @param a recipe a
 * @param b recipe b
 * @return true if a takes less time than b
*/
 bool sortByTime(Recipes a, Recipes b);

/*!
 *@brief Function to apply the settings set by the user
 *@details Filters the recipes based on the filters set
 * @param currentRecipes the recipes to filter
 * @return vector of recipes containing the recipes that pass the filters
*/
 vector<Recipes> applySetting(vector<Recipes> currentRecipes, int timeFilter, int difficultyFilter, const vector<string>& excludedIngredients);

/*!
 *@brief Function to print the settings set by the user
*/
 void printSettings(int timeFilter, int difficultyFilter, int sortFilter, const vector<string>& excludedIngredients);

/*!
 * @brief Function to set settings for the recipes
 * @details User can set filters for difficulty and time and sort
 * @param app the RealmOfRecipes object
*/
 void setSettings(RealmOfRecipes& app);

/*!
 * @brief Function to set difficulty filter
*/
 void handleDifficultyFilter(RealmOfRecipes& app);

/*!
 * @brief Function to handle the time filter
 * @param app the RealmOfRecipes object
 */
void handleTimeFilter(RealmOfRecipes& app);

/*!
 * @brief Function to handle the sort
 * @param app the RealmOfRecipes object
 */
void handleSort(RealmOfRecipes& app);

/*!
 * @brief Function to handle the excluded ingredients
 * @param app the RealmOfRecipes object
 */
void handleExcludedIngredients(RealmOfRecipes& app);

/*!
 * @brief Function to display an invalid choice message
 */
void showInvalidChoiceMessage();

/*!
 * @brief Function that displays a random recipe within the allRecipes array
*/
 void random(const vector<Recipes>& allRecipes, int timeFilter, int difficultyFilter, int sortFilter, const vector<string>& excludedIngredients); ;

/*!
 * @brief Function to search the recipes array by specific name
 * @details Prints out recipes with the searched string in its name
 * @return vector of recipes containing the instance of recipes that contain the searched string
*/
 vector<Recipes> searchByName(vector<Recipes> allRecipes) ;

/*!
 * @brief Function that searches the array of recipes by ingredient(s) separated by commas
 * ingredient(s) will be inputed by the user by typing
 * @details Displays recipes that contains all of the specified ingredient(s)
 * @return vector of recipes containing recipes that contain the ingredient(s)
*/
 vector<Recipes> searchByIngredient(const vector<Recipes>& allRecipes, int timeFilter, int difficultyFilter, int sortFilter, const vector<string>& excludedIngredients) ;
 
 /*!
 * @brief Function to filter the recipes by series
 * @details Displays recipes that are in the specified series
 * @return vector of recipes containing recipes that are in the specified series
*/
 vector<Recipes> searchBySeries(const vector<Recipes>& allRecipes, const vector<string>& allSeries, int timeFilter, int difficultyFilter, int sortFilter, const vector<string>& excludedIngredients) ;



/***************************************************************************************************************************************
 *          Options and main                                                                                                           *
****************************************************************************************************************************************/

/**
 *@brief Function to display the options for the user
 *@details Takes the user input and calls the appropriate function
*/
 void options(RealmOfRecipes& app) ;

#endif // SUPPORT_H