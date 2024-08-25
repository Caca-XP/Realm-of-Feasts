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

using namespace std;




// Function to split a string into a vector of strings
vector<string> split_string(string str, string delimiter, bool lowercase);

/* Function to quit the program
*/
void quit();


/* Function to replace comma space to comma
   Remove empty spaces
*/
string replaceAll(string str, string from, string to);

/* Function to read the whole line of user input instead of just one word
 */
string readLine(bool ignore);

