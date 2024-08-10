/**
 * Application for Unit Testing the Setup reding file of the App
 * @see App.cpp
 * @author Mythical Cooks
 */

# include <iostream>
# include <string>
# include <fstream>
# include "Recipes.h" // Include the header file that contains the definition of the 'Recipes' class
# include <array>
# include <algorithm>
# include <vector>
# include <assert.h>

using namespace std;


//Enum of values of the difficulty levels
enum Level {
    None = 0,
    Easy = 1,
    Medium = 2,
    Hard = 3
};

// Function to split a string into a vector of strings
/// TESTED in SupportClassTest.cpp
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

/**Implementation of Recipes functions */
    /*Default Constructor */
    /// TESTED in SupportClassTest.cpp
    Recipes::Recipes(){
        time = 0;
        difficulty = None;
    };

    /*Defined Constructor*/
    /// TESTED in SupportClassTest.cpp
    Recipes::Recipes(string nm, string ser, string desc, string ing, string ins, int t, enum Level lv) {
        name = nm;
        series = ser;
        description = desc;
        ingredients = split_string(ing, ", ");
        sort(ingredients.begin(), ingredients.end());
        ingredients_str = ing;
        instructions = ins;
        time = t;
        difficulty = lv;

        
    }

    /*Destructor code (idk what this is for)*/
    Recipes::~Recipes() {
        // Destructor code here
    }

    /* Accessor function to get the name of the recipe
        @return name of the recipe
    */
    string Recipes::getName() {
        return name;
    }

    /* Accessor function to get the series of the recipe
        @return series of the recipe
    */
    string Recipes::getSeries() {
        return series;
    }

    /* Accessor function to get the description of the recipe
        @return short description of the recipe
    */
    string Recipes::getDescription() {
        return description;
    }

    /* Accessor function to get the ingredients of the recipe
        @return ingredients of the recipe (list)
    */
    vector<string> Recipes::getIngredients() {
        return ingredients;
    }

    /* Accessor function to get the instructions of the recipe
        @return instructions of the recipe
    */
    string Recipes::getInstructions() {
        return instructions;
    }

    /* Accessor function to get the time of the recipe
        @return time of the recipe in minutes
    */
    int Recipes::getTime() {
        return time;
    }

    /* Accessor function to get the difficulty of the recipe
        @return difficulty of the recipe as an int (1, 2, 3)
    */
    enum Level Recipes::getDifficulty() {
        return difficulty;
    }


/* Vector of the recipes, declared based on number of recipes in the database
*/
vector<Recipes> allRecipes;
vector<string> allSeries;


/* Function to read the data from the file and initialise the allRecipes array
    Creates a new Recipes object for each recipe and adds it to the allRecipes array
    @param filename
*/
void setup(string fileName){
// // read file and initialise allRecipes
    ifstream file(fileName);
    string line;
    int i = 0;
    while (getline(file, line)){
        string name, series, description, ingredients, instructions;
        int time;
        enum Level difficulty;

        //split the line into the different parts
        vector<string> parts = split_string(line, "| ", false);

        name = parts[0];
        series = parts[1];
        description = parts[2];
        ingredients = parts[3];
        instructions = parts[4];
        time = stoi(parts[5]);
        if (parts[6] == "Easy"){
            difficulty = Easy;
        }else if (parts[6] == "Medium"){
            difficulty = Medium;
        }else if (parts[6] == "Hard"){
            difficulty = Hard;
        }

        Recipes newRecipe = Recipes(name, series, description, ingredients, instructions, time, difficulty);
        allRecipes.push_back(newRecipe);
        if (find(allSeries.begin(), allSeries.end(), series) == allSeries.end()){
            allSeries.push_back(series);
        }
        i++;
    }
}

/** 
 * @test Test the setup function using the testdata.txt file
 */
void testSetup(){
    setup("testdata.txt");
    assert(allRecipes.size() == 6);
    assert(allSeries.size() == 5);
    assert(allRecipes[0].getName() == "Pasta");
    assert(allRecipes[0].getSeries() == "Italian");
    assert(allRecipes[0].getDescription() == "A simple pasta recipe");
    assert(allRecipes[0].getIngredients().size() == 3);
    assert(allRecipes[0].getInstructions() == "Boil pasta, add sauce, add cheese");
    assert(allRecipes[0].getTime() == 30);
    assert(allRecipes[0].getDifficulty() == Easy);

    assert(allRecipes[1].getName() == "Pizza");
    assert(allRecipes[1].getSeries() == "Italian");

    assert(allRecipes[2].getName() == "Burger");
    assert(allRecipes[2].getIngredients().size() == 5);

    assert(allRecipes[3].getName() == "Sushi");
    assert(allRecipes[3].getInstructions() == "Cook rice, add fish, wrap in seaweed");

    assert(allRecipes[4].getName() == "Curry");
    assert(allRecipes[4].getDifficulty() == Medium);

    assert(allRecipes[5].getName() == "Pizza Bread");
    assert(allRecipes[5].getSeries() == "NZ");

}

int main(){
    testSetup();
    cout << "testSetup passed" << endl;
    return 0;
}