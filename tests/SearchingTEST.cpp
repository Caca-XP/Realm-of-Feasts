/**
 * Application for Unit Testing the Searching functions of the App
 * @see App.cpp
 * @author Mythical Cooks
 */

# include <iostream>
# include <string>
# include <fstream>
# include "../Recipes.h" // Include the header file that contains the definition of the 'Recipes' class
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

/// @todo maybe check if vector is better than array

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

/* Function to replace comma space to comma
   Remove empty spaces
*/
string replaceAll(string str, string from, string to){
    // check if from and to empty
    if (from.empty() || to.empty()){
        return str;
    }
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos){
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

/* Function to search the recipes array by specific name
    Prints out recipes with the searched string in its name
    @return vector of recipes containing the instance of recipes that contain the searched string
    altered for testing to take @param string searchLine
*/
vector<Recipes> searchByName(string searchLine){
    vector<Recipes> results;
    string search;

    /* Uneeded for testing
    // get the search string from the user
    cout << "Enter the name of the recipe you are looking for: ";
    search = readLine();
    */

    search = searchLine;

    // lowercase the search string and remove leading and trailing spaces
    transform(search.begin(), search.end(), search.begin(), ::tolower);
    search.erase(0, search.find_first_not_of(" "));
    search.erase(search.find_last_not_of(" ") + 1);

    // Go through all the recipes and check if the search string is in the name
    for (int i = 0; i < allRecipes.size(); i++){
        string name = allRecipes[i].getName();

        // lowercase the name of the recipes in the array
        transform(name.begin(), name.end(), name.begin(), ::tolower);

        // check if the search string is in the name of the recipe
        // if it is, add the recipe to the results vector
        if (name.find(search) != string::npos){
            results.push_back(allRecipes[i]);
        }
    }
    // Check that there are recipes based on the search input
    if (results.size() == 0){
        /*Uneeded for testing
        cout << endl << "No recipes found." << endl << endl;
        */
       throw "No recipes found.";

    }else{
        /* Uneeded for testing
        cout << endl << "Results for recipes with \"" << search << "\": " << endl << endl;
        for (int i = 0; i < results.size(); i++){
            cout << results[i].toString() << endl;
        }
        */
    }
    return results;
}


/* Function that searches the array of recipes by ingredient(s) separated by commas
    ingredient(s) will be inputed by the user by typing
    Displays recipes that contains all of the specified ingredient(s)
    @return vector of recipes containing recipes that contain the ingredient(s)
    altered for testing to take @param string searchLine
*/
vector<Recipes> searchByIngredient(string searchLine){
    vector<Recipes> results;
    string search;

    /* Uneeded for testing
    cout << "Enter the ingredient you are looking for (comma separated): ";
    search = readLine();
    */

    search = searchLine;
    // remove leading and trailing spaces
    search.erase(0, search.find_first_not_of(" "));
    search.erase(search.find_last_not_of(" ") + 1);
    // replace all ", " with ","
    search = replaceAll(search, ", ", ",");
    vector<string> searchIngredients = split_string(search, ",");
    // sort the search ingredients
    sort(searchIngredients.begin(), searchIngredients.end());

    // change search to be the string with the ingredients separated by ", "
    search = "";
    for (int i = 0; i < searchIngredients.size(); i++){
        search += searchIngredients[i];
        if (i != searchIngredients.size() - 1){
            search += ", ";
        }
    }

    // Search for recipes that contain the all the ingredients
    for (int i = 0; i < allRecipes.size(); i++){
        vector<string> ingredients = allRecipes[i].getIngredients();
        // use double pointer to check if all the search ingredients are in the recipe ingredients
        if (includes(ingredients.begin(), ingredients.end(), searchIngredients.begin(), searchIngredients.end())){
            results.push_back(allRecipes[i]);
        }

    }
    if (results.size() == 0){
        /* Uneeded for testing
        cout << endl << "No recipes found." << endl << endl;
        */
         throw "No recipes found.";
    }else{
        /* Uneeded for testing
        //Prints the recipes that contains the search string to the results vector
        cout << endl << "Results for recipes with " << search << ": " << endl << endl;
        for (int i = 0; i < results.size(); i++){
            cout << results[i].toString() << endl;
        }
        */
    }
    // return the results
    return results;
}


/* Function to filter the recipes by series
    Displays recipes that are in the specified series
    @return vector of recipes containing recipes that are in the specified series
    altered for testing to take @param string searchLine
*/
vector<Recipes> searchBySeries(string searchLine){
    vector<Recipes> results;
    string search;
    /* Uneeded for testing
    cout << "Enter the series you are looking for: " << endl;
    cout << "To show all series, type 'all'." << endl;
    search = readLine();
    */

    /* Uneeded for testing
    if (search == "all"){
        // print series
        cout << "Series: " << endl;
        for (int i = 0; i < allSeries.size(); i++){
            cout << allSeries[i] << endl;
        }
        cout << "Enter the series you are looking for: " << endl;
        search = readLine(false);
    }
    */

    // lowercase the search string and remove leading and trailing spaces
    transform(search.begin(), search.end(), search.begin(), ::tolower);
    search.erase(0, search.find_first_not_of(" "));
    search.erase(search.find_last_not_of(" ") + 1);

    // Go through all the recipes and check if the search string is in the name
    for (int i = 0; i < allRecipes.size(); i++){
        string series = allRecipes[i].getSeries();

        // lowercase the name of the recipes in the array
        transform(series.begin(), series.end(), series.begin(), ::tolower);

        // check if the search string is in the name of the recipe
        // if it is, add the recipe to the results vector
        if (series.find(search) != string::npos){
            results.push_back(allRecipes[i]);
        }
    }
    // Check that there are recipes based on the search input
    if (results.size() == 0){
        /* Uneeded for testing
        cout << endl << "No recipes found." << endl << endl;
        */
       throw "No recipes found.";
    }else{
        /* Uneeded for testing
        cout << endl << "Results for recipes with \"" << search << "\": " << endl << endl;
        for (int i = 0; i < results.size(); i++){
            cout << results[i].toString() << endl;
        }
        */
    }
    return results;
}

/**
 * @test Testing the searchByName function
 */
void test_searchByName(){

}

/**
 * @test Testing the searchByIngredient function
 */
void test_searchByIngredient(){
}

/**
 * @test Testing the searchBySeries function
 */
void test_searchBySeries(){
}


int main(){
    // Run the tests
    test_searchByName();
    cout << "Search by name tests passed." << endl;
    test_searchByIngredient();
    cout << "Search by ingredient tests passed." << endl;
    test_searchBySeries();
    cout << "Search by series tests passed." << endl;

    return 0;
}