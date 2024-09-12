/*! @file
*@brief contains the declarations of the functions used in the main program
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

# include "Support.h" // Include the header file that contains the definition of the 'Ingredients' class
#include <chrono> // Required for std::chrono::seconds
#include <thread> // Required for std::this_thread::sleep_for


using namespace std;


/*! @memberof 
*@brief Vector containing all recipes
*/
vector<Recipes> app_allRecipes;

/**
 * @brief Function to update all recipes
 * @details Updates the vector of all recipes
 * @param allRecipes the vector of all recipes
 */
void updateAllRecipes(vector<Recipes> allRecipes);

/*! @memberof 
*@brief Time filter for recipes
*/
int app_timeFilter = 0; // 0 for none, 1 for less than 30 minutes, 2 for 30 to 60 minutes, 3 for more than 60 minutes

/**
 * @brief Function to update the time filter
 * @details Updates the time filter for recipes
 * @param timeFilter the time filter for recipes
 */
void updateTimeFilter(int timeFilter);

/*! @memberof 
*@brief difficulty filter of all recipes
*/
int app_difficultyFilter = 0; // 0 for none, 1 for easy, 2 for medium, 3 for hard

/**
 * @brief Function to update the difficulty filter
 * @details Updates the difficulty filter for recipes
 * @param difficultyFilter the difficulty filter for recipes
 */
void updateDifficultyFilter(int difficultyFilter);


/*! @memberof 
*@brief sort filter for all recipes
*/
int app_sortFilter = 0; // 0 for none, 1 for difficulty, 2 for reverse difficulty, 3 for time, 4 for reverse time

/**
 * @brief Function to update the sort filter
 * @details Updates the sort filter for recipes
 * @param sortFilter the sort filter for recipes
 */
void updateSortFilter(int sortFilter);

/*! @memberof 
*@brief Vector containing all the series names of recipes
*/
vector<string> app_allSeries;

/**
 * @brief Function to update all series
 * @details Updates the vector of all series
 * @param allSeries the vector of all series
 */
void updateAllSeries(vector<string> allSeries);

/** 
 * @brief Main function to run the program
 * @details Calls the setup function to initialise the data
 * Calls the options function to display the options for the user
*/
int main();

#endif // APP_H