#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
# include <array>
# include <iterator>
# include <algorithm>
# include <cstdlib>

using namespace std;



//Enum of values of the difficulty levels
enum Level {
    None = 0,
    Easy = 1,
    Medium = 2,
    Hard = 3
};

// Function to split a string into a vector of strings
vector<string> split_string(string str, string delimiter, bool lowercase = true){
    // lowercase the string
    if (lowercase){
        transform(str.begin(), str.end(), str.begin(), ::tolower);
    }
    vector<string> result;
    size_t pos = 0;
    string token;
    while ((pos = str.find(delimiter)) != string::npos){
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

void setup(string fileName){
// // read file and initialise allRecipes
    ifstream file(fileName);
    string line;
    int i = 0;

    // if (getline(file, line)) {
    //     cout << "Header: " << line << endl; // Optionally print the header
    // }
    
    while (getline(file, line)){
        // if line is empty, skip
        if (line.empty() || line == "\t\t\t\t\t\t"){
            continue;
        }

        string name, series, description, ingredients, instructions;
        int time;
        enum Level difficulty;

        //split the line into the different parts
        vector<string> parts = split_string(line, "\t", false);

        name = parts[0];
        series = parts[1];
        description = parts[2];

        // if the start and end of the string are both " then remove them
        if (parts[3].front() == '"' && parts[3].back() == '"'){
            ingredients = parts[3].substr(1, parts[3].length() - 2);
        }else{
            ingredients = parts[3];
        }

        // Ingredients are separated by commas, then separated into number, unit, and ingredient by *
        vector<string> ingredients_parts = split_string(ingredients, ",", false);
        for (string ingredient : ingredients_parts){
            try {
                    vector<string> ingredient_parts = split_string(ingredient, "*", false);
                    if (ingredient_parts.size() < 3) {
                        throw out_of_range("Not enough parts in ingredient");
                    }
                    printf("Ingredient: %s, %s, %s\n", ingredient_parts.at(0).c_str(), ingredient_parts.at(1).c_str(), ingredient_parts.at(2).c_str());
                } catch (const out_of_range& e) {
                    cerr << "*******************************************************************************************************\nError accessing ingredient parts: " << ingredient << "\nException: " << e.what() << endl;
                    continue; // Skip this ingredient and move to the next
            }
            // vector<string> ingredient_parts = split_string(ingredient, "*", false);
            // printf("Ingredient: %s, %s, %s\n", ingredient_parts[0].c_str(), ingredient_parts[1].c_str(), ingredient_parts[2].c_str());
        }

        // if the start and end of the string are both " then remove them
        if (parts[4].front() == '"' && parts[4].back() == '"'){
            try{
                instructions = parts[4].substr(1, parts[4].length() - 2);
            }catch(const out_of_range& e){
                cerr << "*******************************************************************************************************\nError accessing instructions: " << parts[4] << "\nException: " << e.what() << endl;
                continue; // Skip this recipe and move to the next
            }
        }else{
            instructions = parts[4];
        }

        vector<string> instructions_parts = split_string(instructions, "/", false);
        for (string instruction : instructions_parts){
            if (instruction.empty()){
                continue;
            }
            printf("%s\n", instruction.c_str());
        }
        printf("\n\n");
        // Instructions are separated by slashes
        try {
                time = stoi(parts.at(5));
            } catch (const invalid_argument& e) {
                cerr << "Invalid argument for time in line: " << line << "\nException: " << e.what() << endl;
                continue; // Skip this line and move to the next
            } catch (const out_of_range& e) {
                cerr << "Out of range value for time in line: " << line << "\nException: " << e.what() << endl;
                continue; // Skip this line and move to the next
            }               
            
        if (parts[6] == "Easy"){
            difficulty = Easy;
        }else if (parts[6] == "Medium"){
            difficulty = Medium;
        }else if (parts[6] == "Hard"){
            difficulty = Hard;
        }else{
            cerr << "*******************************************************************************************************\nInvalid difficulty level: " << parts[6] << endl;
            continue; // Skip this line and move to the next
        }

        printf("Name: %s\n, series: %s\n, description: %s\n, time: %d\n, difficulty: %d\n\n\n\n", name.c_str(), series.c_str(), description.c_str(), time, difficulty);

        i++;
    }
}


int main() {

    setup("RecipesTest.txt");


    return 0;
}
