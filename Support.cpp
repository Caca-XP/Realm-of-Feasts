#include "Support.h"

// Function to split a string into a vector of strings
vector<string> split_string(string str, string delimiter, bool lowercase = true) {
    // lowercase the string
    if (lowercase) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
    }
    vector<string> result;
    size_t pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != string::npos) {
        token = str.substr(0, pos);
        // remove leading and trailing spaces
        token.erase(0, token.find_first_not_of(" "));
        token.erase(token.find_last_not_of(" ") + 1);

        result.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    str.erase(0, str.find_first_not_of(" "));
    str.erase(str.find_last_not_of(" ") + 1);
    result.push_back(str);
    return result;
}

/* Function to quit the program
*/
void quit() {
    cout << "Goodbye!" << endl;
    exit(0);
}


/* Function to replace comma space to comma
   Remove empty spaces
*/
string replaceAll(string str, string from, string to) {
    // check if from and to empty
    if (from.empty() || to.empty()) {
        return str;
    }
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

/* Function to read the whole line of user input instead of just one word
 */
string readLine(bool ignore = true) {
    string s;
    if (ignore) {
        cin.ignore();
    }
    getline(cin, s);
    return s;
}

