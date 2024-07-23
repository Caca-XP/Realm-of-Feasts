# include <iostream>
# include <string>
# include <fstream>
# include "Recipes.h" // Include the header file that contains the definition of the 'Recipes' class
# include <array>
# include <sstream>
# include <iterator>
# include <algorithm>
# include <cstdlib>
# include <vector>

using namespace std;

/* App class for the realm of feast Recipe finder app
   Contains the implementation of the functions of Recipes Class (Recipes.h)
   
   @version 1.0
   @author Cooks 
*/

enum Level {
    Easy = 1,
    Medium = 2,
    Hard = 3
};

// Function to split a string into a vector of strings
vector<string> split_string(string str, string delimiter){
    // lowercase the string
    transform(str.begin(), str.end(), str.begin(), ::tolower);
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

    /* Function to return a string representation of the recipe
        @return string representation of the recipe
    */
    string Recipes::toString() {
        string result = "Name: " + name + "\n";
        result += "Series: " + series + "\n";
        result += "Description: " + description + "\n";
        result += "Ingredients: " + ingredients_str + "\n";
        result += "Instructions: " + instructions + "\n";
        result += "Time: " + to_string(time) + " minutes\n";
        result += "Difficulty: ";
        if (difficulty == 1){
            result += "Easy\n";
        }
        else if (difficulty == 2){
            result += "Medium\n";
        }
        else if (difficulty == 3){
            result += "Hard\n";
        }
        return result;
    }



/// @todo find number of recipes in data after data base is done

/* Array of the recipes, declared based on number of arrays in the database
*/
const int numRecipes = 6;
array<Recipes, numRecipes> allRecipes;

/* Function to read the data from the file and initialise the allRecipes array
    Creates a new Recipes object for each recipe and adds it to the allRecipes array
*/
void setup(){
// read file and initialise allRecipes
    allRecipes[0] = Recipes("Pasta", "Italian", "A simple pasta recipe", "Pasta, Tomato Sauce, Cheese", "Boil pasta, add sauce, add cheese", 30, Easy);
    allRecipes[1] = Recipes("Pizza", "Italian", "A simple pizza recipe", "Pizza Dough, Tomato Sauce, Cheese", "Roll dough, add sauce, add cheese", 45 , Medium);
    allRecipes[2] = Recipes("Burger", "American", "A simple burger recipe", "Burger Patty, Bun, Lettuce, Tomato, Cheese", "Cook patty, assemble burger", 20 , Easy);
    allRecipes[3] = Recipes("Sushi", "Japanese", "A simple sushi recipe", "Rice, Fish, Seaweed", "Cook rice, add fish, wrap in seaweed", 60 , Hard);
    allRecipes[4] = Recipes("Curry", "Indian", "A simple curry recipe", "Curry Paste, Meat, Vegetables", "Cook meat, add vegetables, add paste", 45 , Medium);
    allRecipes[5] = Recipes("Pizza-Bread", "NZ", "Pizza but with soft bread recipe", "Peperoni, Tomato Sauce, Cheese, Bread Dough", "Roll dough, add sauce, add cheese and pepeponi", 75, Medium);
}

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

void display(array<Recipes, numRecipes> recipes){
    for (int i = 0; i < recipes.size(); i++){
        cout << recipes[i].toString() << endl;
    }
}

/* Function to quit the program
*/
void quit(){
    cout << "Goodbye!" << endl;
    exit(0);
}

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

string readLine(){
    string s;
    cin.ignore();
    getline(cin, s);
    return s;
}

vector<Recipes> searchByName(){
    vector<Recipes> results;
    string search;
    // get the search string from the user
    cout << "Enter the name of the recipe you are looking for: ";
    search = readLine();
    // lowercase the search string and remove leading and trailing spaces
    transform(search.begin(), search.end(), search.begin(), ::tolower);
    search.erase(0, search.find_first_not_of(" "));
    search.erase(search.find_last_not_of(" ") + 1);

    // Go through all the recipes and check if the search string is in the name
    for (int i = 0; i < numRecipes; i++){
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
        cout << endl << "No recipes found." << endl << endl;
    }else{
        cout << endl << "Results for recipes with \"" << search << "\": " << endl << endl;
        for (int i = 0; i < results.size(); i++){
            cout << results[i].toString() << endl;
        }
    }
    return results;
}

vector<Recipes> searchByIngredient(){
    vector<Recipes> results;
    string search;
    cout << "Enter the ingredient you are looking for (comma separated): ";
    search = readLine();
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
    for (int i = 0; i < numRecipes; i++){
        vector<string> ingredients = allRecipes[i].getIngredients();
        // use double pointer to check if all the search ingredients are in the recipe ingredients
        if (includes(ingredients.begin(), ingredients.end(), searchIngredients.begin(), searchIngredients.end())){
            results.push_back(allRecipes[i]);
        }

    }
    if (results.size() == 0){
        cout << endl << "No recipes found." << endl << endl;
    }else{
        //Prints the recipes that contains the search string to the results vector
        cout << endl << "Results for recipes with " << search << ": " << endl << endl;
        for (int i = 0; i < results.size(); i++){
            cout << results[i].toString() << endl;
        }
    }
    // return the results
    return results;
}


void random(){
    int randomIndex = rand() % numRecipes;
    cout << allRecipes[randomIndex].toString() << endl;
}

/* Function to display the options for the user
    Takes the user input and calls the appropriate function
*/
void options(){
    // display the options
    printf("1. Display all recipes\n");
    printf("2. Search for a recipe\n");
    printf("3. Sort recipes\n");
    printf("4. Filter recipes by series\n");
    printf("5. Search by ingredient\n");
    printf("6. Random recipe\n");
    printf("7. Quit\n");

    // get the user choice
    int choice;
    cin >> choice;

    // call the appropriate function based on the user choice
    if (choice == 1){
        display(allRecipes);
    }
    else if (choice == 2){
        searchByName();
    }
    else if (choice == 3){
        while (true){
            // display the sort options
            printf("1. Sort by difficulty\n");
            printf("2. Sort by time\n");
            printf("3. Back\n");

            // get the user choice
            int sortChoice;
            cin >> sortChoice;

            // call the appropriate sort function based on the user choice
            if (sortChoice == 1){
                sort(allRecipes.begin(), allRecipes.end(), sortByDifficulty);
                display(allRecipes);
                break;
            }
            else if (sortChoice == 2){
                sort(allRecipes.begin(), allRecipes.end(), sortByTime);
                display(allRecipes);
                break;
            }
            else if (sortChoice == 3){
                break;
            }
            else{
                // if invalid choice
                cout << "Invalid choice. Please try again." << endl;
                // reset the cin buffer
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    else if (choice == 4){
        // filter();
    }
    else if (choice == 5){
        searchByIngredient();
    }
    else if (choice == 6){
        random();
    }
    else if (choice == 7){
        quit();
    }
    else{
        // if invalid choice
        cout << "Invalid choice. Please try again." << endl;
        // reset the cin buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

}

/* Main function to run the program
* Calls the setup function to initialise the data
* Calls the options function to display the options for the user
*/
int main(){
    // read and initialize the data for recipes
    setup();
    while (true){
        options();
    }
    // 
    return 0;
}