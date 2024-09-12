/*! @file
*@brief supports the implementation of the Ingredients class
*@authors Natasha, Nadia and Bernice
*/
#pragma once
#ifndef RealmOfRecipes_H
#define RealmOfRecipes_H

// Include any necessary libraries or headers here
# include <iostream>
# include <string>
# include <fstream>
# include "Ingredients.h" // Include the header file that contains the definition of the 'Ingredients' class
# include "Recipes.h" // Include the header file that contains the definition of the 'Recipes' class
# include <array>
# include <sstream>
# include <iterator>
# include <algorithm>
# include <cstdlib>
# include <vector>

using namespace std;



/*!
*@class Ingredients
*@brief Represents an ingredient in a recipe with a name, unit, and quantity
*@author Nadia
*/

class RealmOfRecipes {
public:
    /*!
    *@brief Default constructor
    *@details Initializes the name, unit, and quantity of the ingredient with the default values
    */
    RealmOfRecipes();

    /*!
    *@brief Parameterized constructor
    *@details Initializes the name, unit, and quantity of the ingredient with the given values
    *@param q The quantity of the ingredient
    *@param un The unit of the ingredient
    *@param nm The name of the ingredient
    */
    RealmOfRecipes(vector<Recipes> allRecipes, int timeFilter, int difficultyFilter, int sortFilter, vector<string> allSeries);

    /*!
    *@brief Destructor
    *@details Destroys the ingredient object
    */
    ~RealmOfRecipes();

        

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


};

#endif // RealmOfRecipes_H