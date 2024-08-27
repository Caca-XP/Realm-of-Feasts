#pragma once
#ifndef Ingredients_H
#define Ingredients_H

// Include any necessary libraries or headers here
# include <iostream>
# include <string>
# include <fstream>
# include "Ingredients.h" // Include the header file that contains the definition of the 'Ingredients' class
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

class Ingredients {
public:
    /*!
    *@brief Default constructor
    *@details Initializes the name, unit, and quantity of the ingredient with the default values
    */
    Ingredients();

    /*!
    *@brief Parameterized constructor
    *@details Initializes the name, unit, and quantity of the ingredient with the given values
    *@param q The quantity of the ingredient
    *@param un The unit of the ingredient
    *@param nm The name of the ingredient
    */
    Ingredients(double q, const string& un, string nm);

    /*!
    *@brief Destructor
    *@details Destroys the ingredient object
    */
    ~Ingredients();

    /*!
    *@brief Gets the name of the ingredient
    *
    *@return The name of the ingredient
    */
    string getName();

    /*!
    *@brief Gets the unit of the ingredient
    *
    * @return The unit of the ingredient
    */
    string getUnit();

    /*!
    *@brief Gets the quantity of the ingredient
    *
    * @return The quantity of the ingredient
    */
    double getQuantity();


    /*!
    *@brief The string representation of the ingredient
    *
    * @return The string representation of the ingredient
    */
    string toString();



private:
    /*Private data fields*/
    string name;
    string unit;
    double quantity;
};

#endif // Ingredients_H