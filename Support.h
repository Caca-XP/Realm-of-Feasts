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

#endif // SUPPORT_H