/**
 * Application for Unit Testing the Sorting functions of the App
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
    Recipes::Recipes(){
        time = 0;
        difficulty = None;
    };

    /*Defined Constructor*/
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



/* Function to sort the recipes by difficulty
    @param a recipe a
    @param b recipe b
    @return true if a is less difficult than b
*/
bool sortByDifficulty(Recipes a, Recipes b){
    return a.getDifficulty() < b.getDifficulty();
}

/* Function to sort the recipes by time
    @param a recipe a
    @param b recipe b
    @return true if a takes less time than b
*/
bool sortByTime(Recipes a, Recipes b){
    return a.getTime() < b.getTime();
}

/**
 * @test Test the sorting by difficulty functions using vector
 */
void testSortByDifficulty(){
    // Create a vector of recipes
    vector<Recipes> recipes;
    // Create a recipe
    Recipes recipe1("name1", "series1", "description1", "ing1", "ins1", 10, Medium);
    // Add the recipe to the vector
    recipes.push_back(recipe1);
    // Create a recipe
    Recipes recipe2("name2", "series2", "description2", "ing2", "ins2", 20, Easy);
    // Add the recipe to the vector
    recipes.push_back(recipe2);
    // Create a recipe
    Recipes recipe3("name3", "series3", "description3", "ing3", "ins3", 30, Hard);
    // Add the recipe to the vector
    recipes.push_back(recipe3);
    // Sort the recipes by difficulty
    sort(recipes.begin(), recipes.end(), sortByDifficulty);
    // Check if the first recipe is the one with the lowest difficulty
    assert(recipes[0].getName() == "name2");
    // Check if the second recipe is the one with the medium difficulty
    assert(recipes[1].getName() == "name1");
    // Check if the third recipe is the one with the highest difficulty
    assert(recipes[2].getName() == "name3");
}

/**
 * @test Test the sorting by time functions using vector
 */
void testSortByTime(){
    // Create a vector of recipes
    vector<Recipes> recipes;
    // Create a recipe
    Recipes recipe1("name1", "series1", "description1", "ing1", "ins1", 30, Easy);
    // Add the recipe to the vector
    recipes.push_back(recipe1);
    // Create a recipe
    Recipes recipe2("name2", "series2", "description2", "ing2", "ins2", 20, Medium);
    // Add the recipe to the vector
    recipes.push_back(recipe2);
    // Create a recipe
    Recipes recipe3("name3", "series3", "description3", "ing3", "ins3", 10, Hard);
    // Add the recipe to the vector
    recipes.push_back(recipe3);
    // Sort the recipes by time
    sort(recipes.begin(), recipes.end(), sortByTime);
    // Check if the first recipe is the one with the lowest time
    assert(recipes[0].getName() == "name3");
    // Check if the second recipe is the one with the medium time
    assert(recipes[1].getName() == "name2");
    // Check if the third recipe is the one with the highest time
    assert(recipes[2].getName() == "name1");
}

int main(){
    testSortByDifficulty();
    cout << "testSortByDifficulty Passed" << endl;
    testSortByTime();
    cout << "testSortByTime Passed" << endl;
    return 0;
}