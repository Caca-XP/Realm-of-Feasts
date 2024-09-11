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


/** 
 * @brief Main function to run the program
 * @details Calls the setup function to initialise the data
 * Calls the options function to display the options for the user
*/
int main();

#endif // APP_H