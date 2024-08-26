
#include "Ingredients.h"
/***************************************************************************************************************************************
     *          Ingredients Class                                                                                                          *
    ****************************************************************************************************************************************/

    /**Implementation of Ingredients functions */
    /*Default Constructor */
Ingredients::Ingredients() {
    quantity = 0;
};

/*Defined Constructor*/
Ingredients::Ingredients(double q, string un, string nm) 
    : name(nm), quantity(q), unit(un){}

/*Destructor code (idk what this is for) */
Ingredients::~Ingredients() {
    // Destructor code here
}

/* Accessor function to get the name of the ingredient
    @return name of the ingredient
*/
string Ingredients::getName() {
    return name;
}

/* Accessor function to get the unit of the ingredient
    @return unit of the ingredient
*/
string Ingredients::getUnit() {
    return unit;
}

/* Accessor function to get the quantity of the ingredient
    @return quantity of the ingredient
*/
double Ingredients::getQuantity() {
    return quantity;
}

/* Function to return a string representation of the ingredient
    @return string representation of the ingredient
*/
string Ingredients::toString() {
    string result = "";
    if (quantity != 0) {
        result += to_string(quantity);
        if (result.find('.') != string::npos) {
            result.erase(result.find_last_not_of('0') + 1, string::npos);
            if (result.back() == '.') {
                result.pop_back();
            }
        }
        result += " ";
    }
    if (unit != "null") {
        result += unit + " ";
    }
    result += name;
    return result;
}


