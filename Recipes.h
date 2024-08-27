/*! @file
*@brief  file supports the implementation of the Recipes class
*@authors Natasha, Nadia and Bernice
*/
#pragma once
#ifndef RECIPES_H
#define RECIPES_H

// Include any necessary libraries or headers here
# include <iostream>
# include <string>
# include <fstream>
#include <vector>
#include "Ingredients.h"// Include the header file that contains the definition of the 'Ingredients' class
# include <array>
# include <sstream>
# include <iterator>
# include <algorithm>
# include <cstdlib>
using namespace std;

/*! 
* @enum Level
* @brief Enum of values of the difficulty levels
*/
enum Level {
    None = 0,
    Easy = 1,
    Medium = 2,
    Hard = 3
};

/*!
*@class Recipes
*@brief Represents a recipe in a recipe with a name, series, description, ingredients, instructions, time, and difficulty level
*@author Nadia
*/
class Recipes {
    public:
   /*!
    *@brief Default constructor for Recipes class
    *@details Initializes a recipe with the default values
    */
    Recipes();

    /*!
    *@brief Parameterized constructor for Recipes class
    *@details Initializes a recipe with the given values
    *@param nm The name of the recipe
    *@param ser The series of the recipe
    *@param desc The description of the recipe
    *@param ing List of ingredients for the recipe
    *@param ins The instructions of the recipe
    *@param t The time of the recipe
    *@param lv The difficulty level of the recipe
    */
    Recipes(string nm, string ser, string desc, vector<Ingredients>, string ins, int t, enum Level lv);

    /*!
    *@brief Destructor for Recipes class
    *@details Destroys the recipe object
    */
    ~Recipes();

    /*!
    *@brief Gets the name of the recipe
    *
    * @return The name of the recipe
    */
    string getName();

    /*!
    *@brief Gets the series of the recipe
    *
    * @return The series of the recipe
    */
    string getSeries();

    /*!
    *@brief Gets the description of the recipe
    *
    * @return The description of the recipe
    */
    string getDescription();

    /*!
    *@brief Gets the ingredients of the recipe
    *
    * @return The ingredients of the recipe
    */
    vector<Ingredients> getIngredients();

    /*!
    *@brief Gets the names of the ingredients of the recipe
    *
    * @return The names of the ingredients of the recipe
    */
    vector<string> getIngredientsNames();

    /*!
    *@brief Gets the instructions of the recipe
    *
    * @return The instructions of the recipe
    */
    string getInstructions();

    /*!
    *@brief Gets the time of the recipe
    *
    *@return The time of the recipe
    */
    int getTime();

    /*!
    *@brief Gets the difficulty level of the recipe
    *
    * @return The difficulty level of the recipe
    */
    enum Level getDifficulty();

    /*!
    *@brief The string representation of the recipe
    *
    * @return The string representation of the recipe
    */
    string toString();

    /*!
    *@brief The short string representation of the recipe
    *@details The short string representation of the recipe without the instructions
    *@return The short string representation of the recipe
    */
    string toStringShort();

private:
    /*Private data fields*/
    string name; /*! @brief The name of the recipe  */
    string series;  /*! @memberof series of the recipe  */ 
    string description;/*!< @variable The description of the recipe  */
    vector<Ingredients> ingredients;/*!< The list of ingredients of the recipe  */
    string ingredients_str;/*!< The string representation of the list of ingredients for the recipe  */
    vector<string> ingredient_names;/*!< The names of the ingredients needed for recipe  */
    string instructions;/*!< The instructions for preparing the recipe  */
    int time;/*!< The time required for the recipe  */
    enum Level difficulty;/*!< The difficulty of the recipe  */
};

#endif // RECIPES_H