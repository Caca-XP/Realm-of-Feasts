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
*@class RealmOfRecipes
*@brief Represents a realm of recipes with a vector of recipes, time filter, difficulty filter, sort filter, and series filter
*@author Nadia
*/

class RealmOfRecipes {
public:
    /*!
    *@brief Default constructor
    *@details Initializes a realm of recipes with the default values
    */
    RealmOfRecipes();

    /*!
    *@brief Parameterized constructor
    *@details Initializes a realm of recipes with the given values
    */
    RealmOfRecipes(const vector<Recipes>& recipes, int time, int difficulty, int sort, const vector<string>& series, const vector<string>& excluded);
    /*!
    *@brief Destructor
    *@details Destroys the ingredient object
    */
    ~RealmOfRecipes();

        

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

    /*! @memberof
    *@brief Vector containing all the excluded ingredients
    */
    vector<string> excludedIngredients;


};

#endif // RealmOfRecipes_H