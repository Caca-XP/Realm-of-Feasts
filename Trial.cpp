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

    if (getline(file, line)) {
        cout << "Header: " << line << endl; // Optionally print the header
    }

    while (getline(file, line)){
        // if line is empty, skip
        if (line.empty() || line == "\t\t\t\t\t\t"){
            printf("Empty line\n");
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
        ingredients = parts[3].substr(1, parts[3].length() - 2);

        printf("Ingredients: %s\n\n\n\n", ingredients.c_str());

        // Ingredients are separated by commas, then separated into number, unit, and ingredient by *
        vector<string> ingredients_parts = split_string(ingredients, ",", false);
        for (string ingredient : ingredients_parts){
            vector<string> ingredient_parts = split_string(ingredient, "*", false);
            printf("Ingredient: %s, %s, %s\n", ingredient_parts[0].c_str(), ingredient_parts[1].c_str(), ingredient_parts[2].c_str());
        }
        instructions = parts[4];
        // Instructions are separated by slashes
        time = stoi(parts[5]);
        if (parts[6] == "Easy"){
            difficulty = Easy;
        }else if (parts[6] == "Medium"){
            difficulty = Medium;
        }else if (parts[6] == "Hard"){
            difficulty = Hard;
        }

        printf("Name: %s\n, series: %s\n, description: %s\n, ingredients: %s\n, instructions: %s\n, time: %d\n, difficulty: %d\n\n", name.c_str(), series.c_str(), description.c_str(), ingredients.c_str(), instructions.c_str(), time, difficulty);

        i++;
    }
}


int main() {

    setup("RecipesTest.txt");


    return 0;
}
