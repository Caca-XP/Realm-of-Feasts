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
vector<Recipes> allRecipes;

/*! @memberof 
*@brief Time filter for recipes
*/
int timeFilter = 0; // 0 for none, 1 for less than 30 minutes, 2 for 30 to 60 minutes, 3 for more than 60 minutes

/*! @memberof 
*@brief difficulty filter of all recipes
*/
int difficultyFilter = 0; // 0 for none, 1 for easy, 2 for medium, 3 for hard

/*! @memberof 
*@brief sort filter for all recipes
*/
int sortFilter = 0; // 0 for none, 1 for difficulty, 2 for reverse difficulty, 3 for time, 4 for reverse time

/*! @memberof 
*@brief Vector containing all the series names of recipes
*/
vector<string> allSeries;

/** 
 * @brief Main function to run the program
 * @details Calls the setup function to initialise the data
 * Calls the options function to display the options for the user
*/
int main();

#endif // APP_H