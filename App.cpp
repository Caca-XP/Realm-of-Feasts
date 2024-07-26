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

//Enum of values of the difficulty levels
enum Level {
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


/* Vector of the recipes, declared based on number of recipes in the database
*/
vector<Recipes> allRecipes;
int timeFilter = 0;
int difficultyFilter = 0;

vector<string> allSeries;

/* Function to read the data from the file and initialise the allRecipes array
    Creates a new Recipes object for each recipe and adds it to the allRecipes array
*/
void setup(){
// // read file and initialise allRecipes
    ifstream file("testdata.txt");
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

/* Function to display recipes specified in the param
    @param array of recipes
 */
void display(vector<Recipes> recipes){
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

/* Function to read the whole line of user input instead of just one word
 */
string readLine(bool ignore = true){
    string s;
    if (ignore){
        cin.ignore();
    }
    getline(cin, s);
    return s;
}

/* Function to search the recipes array by specific name
    Prints out recipes with the searched string in its name
    @return vector of recipes containing the instance of recipes that contain the searched string
*/
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
        cout << endl << "No recipes found." << endl << endl;
    }else{
        cout << endl << "Results for recipes with \"" << search << "\": " << endl << endl;
        for (int i = 0; i < results.size(); i++){
            cout << results[i].toString() << endl;
        }
    }
    return results;
}

/* Function that searches the array of recipes by ingredient(s) separated by commas
    ingredient(s) will be inputed by the user by typing
    Displays recipes that contains all of the specified ingredient(s)
    @return vector of recipes containing recipes that contain the ingredient(s)
*/
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
    for (int i = 0; i < allRecipes.size(); i++){
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

/* Function to filter the recipes by series
    Displays recipes that are in the specified series
    @return vector of recipes containing recipes that are in the specified series
*/
vector<Recipes> searchBySeries(){
    vector<Recipes> results;
    string search;
    cout << "Enter the series you are looking for: " << endl;
    cout << "To show all series, type 'all'." << endl;
    search = readLine();
    if (search == "all"){
        // print series
        cout << "Series: " << endl;
        for (int i = 0; i < allSeries.size(); i++){
            cout << allSeries[i] << endl;
        }
        cout << "Enter the series you are looking for: " << endl;
        search = readLine(false);
    }
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
        cout << endl << "No recipes found." << endl << endl;
    }else{
        cout << endl << "Results for recipes with \"" << search << "\": " << endl << endl;
        for (int i = 0; i < results.size(); i++){
            cout << results[i].toString() << endl;
        }
    }
    return results;
}


/* Function to set filters for the recipes
    Filters the recipes based on the user input
    @return vector of recipes containing recipes that are filtered
*/
vector<Recipes> setFilters(vector<Recipes> currentRecipes){
    vector<Recipes> results;
    
    while (true){
        printf("Current filters: \n");
        if (difficultyFilter != 0){
            if (difficultyFilter == 1){
                printf("Difficulty: Easy \n");
            }
            else if (difficultyFilter == 2){
                printf("Difficulty: Medium \n");
            }
            else if (difficultyFilter == 3){
                printf("Difficulty: Hard \n");
            }
        }
        if (timeFilter != 0){
            if (timeFilter == 1){
                printf("Time: Less than 30 minutes \n");
            }
            else if (timeFilter == 2){
                printf("Time: 30 to 60 minutes \n");
            }
            else if (timeFilter == 3){
                printf("Time: More than 60 minutes \n");
            }
        }
        if (difficultyFilter == 0 && timeFilter == 0){
            printf("None \n");
        }
        printf("\n");

        // display the filter options
        printf("1. Filter by difficulty\n");
        printf("2. Filter by time\n");
        printf("3. Reset filters\n");
        printf("4. Back\n");

        // get the user choice
        int filterChoice;
        cin >> filterChoice;

        // call the appropriate filter function based on the user choice
        if (filterChoice == 1){
            while (true){
                // display the filter options
                printf("1. Easy\n");
                printf("2. Medium\n");
                printf("3. Hard\n");
                printf("4. Back\n");

                // get the user choice
                int difficultyChoice;
                cin >> difficultyChoice;

                // call the appropriate filter function based on the user choice
                if (difficultyChoice == 1 || difficultyChoice == 2 || difficultyChoice == 3){
                    difficultyFilter = difficultyChoice;
                    break;
                }
                else if (difficultyChoice == 4){
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
        else if (filterChoice == 2){
            while (true){
                // display the filter options
                printf("1. Less than 30 minutes\n");
                printf("2. 30 to 60 minutes\n");
                printf("3. More than 60 minutes\n");
                printf("4. Back\n");

                // get the user choice
                int timeChoice;
                cin >> timeChoice;

                // call the appropriate filter function based on the user choice
                if (timeChoice == 1 || timeChoice == 2 || timeChoice == 3){
                    timeFilter = timeChoice;
                    break;
                }
                else if (timeChoice == 4){
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
        }else if (filterChoice == 3){
            timeFilter = 0;
            difficultyFilter = 0;
        }else if (filterChoice == 4){
            break;
        }else{
            // if invalid choice
            cout << "Invalid choice. Please try again." << endl;
            // reset the cin buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        

    }
    printf("Results after filtering: \n\n");
    // filter the recipes based on the filters set
    for (int i = 0; i < currentRecipes.size(); i++){
        if (difficultyFilter != 0 && currentRecipes[i].getDifficulty() != difficultyFilter){
            continue;
        }
        if (timeFilter == 1 && currentRecipes[i].getTime() >= 30){
            continue;
        }
        if (timeFilter == 2 && (currentRecipes[i].getTime() < 30 || currentRecipes[i].getTime() > 60)){
            continue;
        }
        if (timeFilter == 3 && currentRecipes[i].getTime() <= 60){
            continue;
        }
        results.push_back(currentRecipes[i]);
    }
    if (results.size() == 0){
        cout << endl << "No recipes found." << endl << endl;
    }
    return results;
}


/*Function that displays a random recipe within the allRecipes array
*/
void random(){
    int randomIndex = rand() % allRecipes.size();
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
    printf("4. Search recipes by series\n");
    printf("5. Search by ingredient\n");
    printf("6. Set filters\n");
    printf("7. Random recipe\n");
    printf("8. Quit\n");

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
        searchBySeries();
    }
    else if (choice == 5){
        searchByIngredient();
    }
    else if (choice == 6){
        vector<Recipes> r = setFilters(allRecipes);
        for (int i = 0; i < r.size(); i++){
            cout << r[i].toString() << endl;
        }
    }
    else if (choice == 7){
        random();
    }
    else if (choice == 8){
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
    
    return 0;
}