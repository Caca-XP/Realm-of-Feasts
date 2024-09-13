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


/* Function to set the color of the text in the console
*/
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/* Function to get the current text color
*/ 
int getCurrentColor() {
    // Get the handle to the console output
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Structure to hold console buffer information
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // Get the current console screen buffer information
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        // Extract and return the current text attribute (color)
        return csbi.wAttributes;
    }

    return -1; // Return -1 if getting the information fails
}

/***************************************************************************************************************************************
 *          Setup functions                                                                                                            *
****************************************************************************************************************************************/



/**
 * Function to process the ingredients string
 * Splits the ingredients string by commas and then by *
 * @param ingred the ingredients string
 * @return vector of Ingredients objects
 */
vector<Ingredients> process_ingred(string ingred) {

    string ingredients;
    // if the start and end of the string are both " then remove them
    if (ingred.front() == '"' && ingred.back() == '"') {
        ingredients = ingred.substr(1, ingred.length() - 2);
    }
    else {
        ingredients = ingred;
    }
    vector<Ingredients> ingredients_list;
    // Ingredients are separated by commas, then separated into number, unit, and ingredient by *
    vector<string> ingredients_parts = split_string(ingredients, ",", false);
    for (string ingredient : ingredients_parts) {
        try {
            vector<string> ingredient_units = split_string(ingredient, "*", false);
            if (ingredient_units.size() < 3) {
                throw out_of_range("Not enough parts in ingredient");
                continue;
            }
            ingredients_list.push_back(Ingredients(stod(ingredient_units[0]), ingredient_units[1], ingredient_units[2]));

        }
        catch (const out_of_range& e) {
            cerr << "*******************************************************************************************************\nError accessing ingredient parts: " << ingredient << "\nException: " << e.what() << endl;
            continue; // Skip this ingredient and move to the next
        }


        // printf("Ingredient: %s, %s, %s\n", ingredient_parts[0].c_str(), ingredient_parts[1].c_str(), ingredient_parts[2].c_str());
    }
    return ingredients_list;
}

/**
 * Function to process the instructions string
 * Replaces || with new line
 * @param instruct the instructions string
 * @return the processed instructions string
 */
 string process_instructions(const string& instruct) {
    string instructions;
    // if the start and end of the string are both " then remove them
    if (instruct.front() == '"' && instruct.back() == '"') {
        try {
            instructions = instruct.substr(1, instruct.length() - 2);
        }
        catch (const out_of_range& e) {
            cerr << "*******************************************************************************************************\nError accessing instructions: " << instructions << "\nException: " << e.what() << endl;
        }
    }
    else {
        instructions = instruct;
    }

    instructions = replaceAll(instructions, "||", "\n");

    return instructions;

}

/**
 * Function to process the time string
 * Converts the time string to an integer
 * @param time_str the time string
 * @return the time as an integer
 */
 int process_time(const string& time_str) {
    int time;
    try {
        time = stoi(time_str);
    }
    catch (const invalid_argument& e) {
        cerr << "*******************************************************************************************************\nInvalid argument for time: " << time_str << "\nException: " << e.what() << endl;
        return -1;
    }
    catch (const out_of_range& e) {
        cerr << "*******************************************************************************************************\nOut of range value for time: " << time_str << "\nException: " << e.what() << endl;
        return -1;
    }
    return time;
}

//Enum of values of the difficulty levels
Level process_difficulty(const string& difficulty_str) {
    Level difficulty;
    if (difficulty_str == "Easy") {
        difficulty = Easy;
    }
    else if (difficulty_str == "Medium") {
        difficulty = Medium;
    }
    else if (difficulty_str == "Hard") {
        difficulty = Hard;
    }
    else {
        cerr << "*******************************************************************************************************\nInvalid difficulty level: " << difficulty_str << endl;
        return None;
    }
    return difficulty;
}


/**
 * Function to read the data from the file and initialise the allRecipes array
 * Creates a new Recipes object for each recipe and adds it to the allRecipes array
 * @param fileName the name of the file to read the data from
*/
void setup(string fileName, RealmOfRecipes& app) {
    // // read file and initialise allRecipes
    ifstream file(fileName);
    string line;
    int i = 0;

    if (getline(file, line)) {
        // cout << "Header: " << line << endl; // Optionally print the header
        // skip the header
    }

    while (getline(file, line)) {
        // if line is empty, skip
        // if line is only tabs, skip
        string alltabs = replaceAll(line, "\t", "");
        if (line.empty() || alltabs == "") {
            continue;
        }

        string name, series, description, instructions;
        int time;
        Level difficulty;

        //split the line into the different parts
        vector<string> parts = split_string(line, "\t", false);

        name = parts[0];
        series = parts[1];
        description = parts[2];
        vector<Ingredients> ingredients_parts = process_ingred(parts[3]);
        instructions = process_instructions(parts[4]);
        time = process_time(parts[5]);
        difficulty = process_difficulty(parts[6]);

        Recipes newRecipe = Recipes(name, series, description, ingredients_parts, instructions, time, difficulty);
        app.allRecipes.push_back(newRecipe);
        if (find(app.allSeries.begin(), app.allSeries.end(), series) == app.allSeries.end()) {
            app.allSeries.push_back(series);
        }
        i++;


    }
}

/***************************************************************************************************************************************
 *          Options functions                                                                                                          *
****************************************************************************************************************************************/

/**
 * Function to display recipes specified in the param
 * @param array of recipes
 */
 void display(vector<Recipes> recipes, bool isShort = true) {
    if (isShort) {
        for (int i = 0; i < recipes.size(); i++) {
            cout << recipes[i].toStringShort() << endl;
        }
    }
    else {
        for (int i = 0; i < recipes.size(); i++) {
            cout << recipes[i].toString() << endl;
        }
    }
}

/**
 * Function to sort the recipes by difficulty
 * @param a recipe a
 * @param b recipe b
 * @return true if a is less difficult than b
*/
 bool sortByDifficulty(Recipes a, Recipes b) {
    return a.getDifficulty() < b.getDifficulty();
}

/**
 * Function to sort the recipes by time
 * @param a recipe a
 * @param b recipe b
 * @return true if a takes less time than b
*/
 bool sortByTime(Recipes a, Recipes b) {
    return a.getTime() < b.getTime();
}


/***************************************************************************************************************************************
 *          Set filters and random                                                                                                     *
****************************************************************************************************************************************/


/**
 * Function to apply the settings set by the user
 * Filters the recipes based on the filters set
 * @param currentRecipes the recipes to filter
 * @return vector of recipes containing the recipes that pass the filters
*/
 vector<Recipes> applySetting(vector<Recipes> currentRecipes, int timeFilter, int difficultyFilter) {

    vector<Recipes> results;

    // filter the recipes based on the filters set
    for (int i = 0; i < currentRecipes.size(); i++) {
        if (difficultyFilter != 0 && currentRecipes[i].getDifficulty() != difficultyFilter) {
            continue;
        }
        if (timeFilter == 1 && currentRecipes[i].getTime() >= 30) {
            continue;
        }
        if (timeFilter == 2 && (currentRecipes[i].getTime() < 30 || currentRecipes[i].getTime() > 60)) {
            continue;
        }
        if (timeFilter == 3 && currentRecipes[i].getTime() <= 60) {
            continue;
        }
        results.push_back(currentRecipes[i]);
    }
    if (results.size() == 0) {
		// set colour to red
		setColor(4);

        cout << endl << "No recipes found." << endl << endl;
    }
    return results;
}

/**
 * Function to print the settings set by the user
*/
 void printSettings(int timeFilter, int difficultyFilter, int sortFilter) {
	// set colour to light yellow
	setColor(14);

    printf("\nCurrent filters: \n");
    if (difficultyFilter != 0) {
        if (difficultyFilter == 1) {
			//set colour to green
			setColor(10);
            printf("Difficulty: Easy \n");
        }
        else if (difficultyFilter == 2) {
			//set colour to yellow
			setColor(6);
            printf("Difficulty: Medium \n");
        }
        else if (difficultyFilter == 3) {
			//set colour to red
			setColor(12);
            printf("Difficulty: Hard \n");
        }
    }
    if (timeFilter != 0) {
        if (timeFilter == 1) {
			//set colour to green
			setColor(10);
            printf("Time: Less than 30 minutes \n");
        }
        else if (timeFilter == 2) {
			//set colour to yellow
			setColor(6);
            printf("Time: 30 to 60 minutes \n");
        }
        else if (timeFilter == 3) {
			//set colour to red
			setColor(12);
            printf("Time: More than 60 minutes \n");
        }
    }
    if (difficultyFilter == 0 && timeFilter == 0) {
		// set colour to white
		setColor(15);
        printf("None \n");
    }
	// set colour to light yellow
	setColor(14);
    printf("Current sorting: \n");
    if (sortFilter != 0) {
        if (sortFilter == 1) {
			//set colour to light blue
			setColor(11);
            printf("Sort by difficulty \n");
        }
        else if (sortFilter == 2) {
			//set colour to blue
			setColor(11);
            printf("Sort by difficulty reverse \n");
        }
        else if (sortFilter == 3) {
			//set colour to light magenta
			setColor(13);
            printf("Sort by time \n");
        }
        else if (sortFilter == 4) {
			//set colour to magenta
			setColor(13);
            printf("Sort by time reverse \n");
        }
    }
    else {
		//set colour to white
		setColor(15);
        printf("None \n");
    }

    printf("\n");
}

/**
 * Function to set settings for the recipes
 * User can set filters for difficulty and time
 * User can set sorting for the recipes
*/
 void setSettings(RealmOfRecipes& app){

    while (true) {
        printSettings(app.timeFilter, app.difficultyFilter, app.sortFilter);

        // set colour to blue
		setColor(3);

        // display the filter options
        printf("1. Filter by difficulty\n");
        printf("2. Filter by time\n");
        printf("3. Reset filters\n");
        printf("4. Set sort\n");
        printf("5. Reset sort\n");
        printf("6. Back\n");

		// get the user choice (colour to grey 8)
		setColor(8);
        int filterChoice;
        cin >> filterChoice;

        // call the appropriate filter function based on the user choice
        if (filterChoice == 1) {
            while (true) {
                // display the filter options
				// set colour to green
				setColor(10);
                printf("1. Easy\n");

				// set colour to yellow
				setColor(6);
                printf("2. Medium\n");

				// set colour to red
				setColor(12);
                printf("3. Hard\n");

				// set colour to white
				setColor(15);
                printf("4. Back\n");

				// get the user choice (colour to grey 8)
				setColor(8);
                int difficultyChoice;
                cin >> difficultyChoice;

                // call the appropriate filter function based on the user choice
                if (difficultyChoice == 1 || difficultyChoice == 2 || difficultyChoice == 3) {
                    app.difficultyFilter = difficultyChoice;
                    break;
                }
                else if (difficultyChoice == 4) {
                    break;
                }
                else {
                    // if invalid choice
                    cout << "Invalid choice. Please try again." << endl;
                    // reset the cin buffer
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }
        else if (filterChoice == 2) {
            while (true) {
                // display the filter options
				// set colour to green
				setColor(10);
                printf("1. Less than 30 minutes\n");
				// set colour to yellow
				setColor(6);
                printf("2. 30 to 60 minutes\n");
				// set colour to red
				setColor(12);
                printf("3. More than 60 minutes\n");
				// set colour to white
				setColor(15);
                printf("4. Back\n");

				// get the user choice (colour to grey 8)
				setColor(8);
                int timeChoice;
                cin >> timeChoice;

                // call the appropriate filter function based on the user choice
                if (timeChoice == 1 || timeChoice == 2 || timeChoice == 3) {
                    app.timeFilter = timeChoice;
                    break;
                }
                else if (timeChoice == 4) {
                    break;
                }
                else {
                    // if invalid choice
					// set colour to red
					setColor(4);
                    cout << "Invalid choice. Please try again." << endl;
                    // reset the cin buffer
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }
        else if (filterChoice == 3) {
            app.timeFilter = 0;
            app.difficultyFilter = 0;
        }
        else if (filterChoice == 4) {
            while (true) {
                // display the sort options
				// set colour to light blue
				setColor(11);
                printf("1. Sort by difficulty\n");
				// set colour to blue
				setColor(11);
                printf("2. Sort by difficulty reverse\n");

				// set colour to light magenta
				setColor(13);
                printf("3. Sort by time\n");
				// set colour to magenta
				setColor(13);
                printf("4. Sort by time reverse\n");

				// set colour to white
				setColor(15);
                printf("5. Back\n");

				// get the user choice (colour to grey 8)
				setColor(8);
                int sortChoice;
                cin >> sortChoice;

                // call the appropriate sort function based on the user choice
                if (sortChoice == 1) {
                    sort(app.allRecipes.begin(), app.allRecipes.end(), sortByDifficulty);
                    app.sortFilter = 1;
                    break;
                }
                else if (sortChoice == 2) {
                    sort(app.allRecipes.begin(), app.allRecipes.end(), sortByDifficulty);
                    reverse(app.allRecipes.begin(), app.allRecipes.end());
                    app.sortFilter = 2;
                    break;
                }
                else if (sortChoice == 3) {
                    sort(app.allRecipes.begin(), app.allRecipes.end(), sortByTime);
                    app.sortFilter = 3;
                    break;
                }
                else if (sortChoice == 4) {
                    sort(app.allRecipes.begin(), app.allRecipes.end(), sortByTime);
                    reverse(app.allRecipes.begin(), app.allRecipes.end());
                    app.sortFilter = 4;
                    break;
                }
                else if (sortChoice == 5) {
                    break;
                }
                else {
                    // if invalid choice
					// set colour to red
					setColor(4);
                    cout << "Invalid choice. Please try again." << endl;
                    // reset the cin buffer
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

        }
        else if (filterChoice == 5) {
            app.sortFilter = 0;
        }
        else if (filterChoice == 6) {
            break;
        }
        else {
            // if invalid choice
			// set colour to red
			setColor(4);
            cout << "Invalid choice. Please try again." << endl;
            // reset the cin buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    }
    // Ask the user whether to apply the filters and print the results
    while (true) {
		// display the apply options
		// set colour to blue
		setColor(3);
        printf("1. Save settings and print all recepies with settings applied\n");
        printf("2. Save settings and back\n");

		// get the user choice (colour to grey 8)
		setColor(8);
        int applyChoice;
        cin >> applyChoice;

        // call the appropriate function based on the user choice
        if (applyChoice == 1) {
            vector<Recipes> applied = applySetting(app.allRecipes, app.timeFilter, app.difficultyFilter);
			// display the recipes with the settings applied
			// set colour to white 7
			setColor(7);
            display(applied);
            break;
        }
        else if (applyChoice == 2) {
			// set colour to green
			setColor(2);
            printf("Settings saved.\n\n");
            break;
        }
        else {
            // if invalid choice
			// set colour to red
			setColor(4);
            cout << "Invalid choice. Please try again." << endl;
            // reset the cin buffer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
    }
}


/**
 * Function that displays a random recipe within the allRecipes array
*/
 void random(vector<Recipes> allRecipes, int timeFilter, int difficultyFilter, int sortFilter) {
    vector<Recipes> applied = applySetting(allRecipes, timeFilter, difficultyFilter);
    int randomIndex = rand() % applied.size();
    printSettings(timeFilter, difficultyFilter, sortFilter);
	// set colour to white 7
	setColor(7);
    cout << applied[randomIndex].toString() << endl;
}


/***************************************************************************************************************************************
 *          Search functions                                                                                                           *
****************************************************************************************************************************************/

/**
 * Function to search the recipes array by specific name
 * Prints out recipes with the searched string in its name
 * @return vector of recipes containing the instance of recipes that contain the searched string
*/
 vector<Recipes> searchByName(vector<Recipes> allRecipes) {
    vector<Recipes> results;
    string search;
    // get the search string from the user
	// set colour to blue 9
	setColor(9);
    cout << "Enter the name of the recipe you are looking for: ";

	// get user input (colour to grey 8)
	setColor(8);
    search = readLine(true);
    // lowercase the search string and remove leading and trailing spaces
    transform(search.begin(), search.end(), search.begin(), ::tolower);
    search.erase(0, search.find_first_not_of(" "));
    search.erase(search.find_last_not_of(" ") + 1);

    // Go through all the recipes and check if the search string is in the name
    for (int i = 0; i < allRecipes.size(); i++) {
        string name = allRecipes[i].getName();

        // lowercase the name of the recipes in the array
        transform(name.begin(), name.end(), name.begin(), ::tolower);

        // check if the search string is in the name of the recipe
        // if it is, add the recipe to the results vector
        if (name.find(search) != string::npos) {
            results.push_back(allRecipes[i]);
        }
    }
    // Check that there are recipes based on the search input
    if (results.size() == 0) {
		// set colour to red
		setColor(4);
        cout << endl << "No recipes found." << endl << endl;
    }
    else {
		//Prints the recipes that contains the search string to the results vector
		// set colour to white 7
		setColor(7);
        cout << endl << "Results for recipes with \"" << search << "\": " << endl << endl;
        for (int i = 0; i < results.size(); i++) {
            cout << results[i].toString() << endl;
        }
    }
    return results;
}

/**
 * Function that searches the array of recipes by ingredient(s) separated by commas
 * ingredient(s) will be inputed by the user by typing
 * Displays recipes that contains all of the specified ingredient(s)
 * @return vector of recipes containing recipes that contain the ingredient(s)
*/
 vector<Recipes> searchByIngredient(vector<Recipes> allRecipes, int timeFilter, int difficultyFilter, int sortFilter) {
    vector<Recipes> results;
    string search;

	// get the search string from the user
	// set colour to blue 9
	setColor(9);
    cout << "Enter the ingredient you are looking for (comma separated): ";

	// get user input (colour to grey 8)
	setColor(8);
    search = readLine(true);
    // remove leading and trailing spaces
    search.erase(0, search.find_first_not_of(" "));
    search.erase(search.find_last_not_of(" ") + 1);

    vector<string> searchIngredients = split_string(search, ",", true);
    // sort the search ingredients
    sort(searchIngredients.begin(), searchIngredients.end());

    // change search to be the string with the ingredients separated by ", "
    search = "";
    for (int i = 0; i < searchIngredients.size(); i++) {
        search += searchIngredients[i];
        if (i != searchIngredients.size() - 1) {
            search += ", ";
        }
    }

    // Search for recipes that contain the all the ingredients
    vector<Recipes> applied = applySetting(allRecipes, timeFilter, difficultyFilter);
    for (int i = 0; i < applied.size(); i++) {
        vector<string> ingredients = applied[i].getIngredientsNames();
        // use double pointer to check if all the search ingredients are in the recipe ingredients
        if (includes(ingredients.begin(), ingredients.end(), searchIngredients.begin(), searchIngredients.end())) {
            results.push_back(applied[i]);
        }

    }
    printSettings(timeFilter, difficultyFilter, sortFilter);
    if (results.size() == 0) {
		// set colour to red
		setColor(4);
        cout << endl << "No recipes found." << endl << endl;
    }
    else {
        //Prints the recipes that contains the search string to the results vector
		// set colour to white 7
		setColor(7);
        cout << endl << "Results for recipes with " << search << ": " << endl << endl;
        for (int i = 0; i < results.size(); i++) {
            cout << results[i].toString() << endl;
        }
    }
    // return the results
    return results;
}

/**
 * Function to filter the recipes by series
 * Displays recipes that are in the specified series
 * @return vector of recipes containing recipes that are in the specified series
*/
 vector<Recipes> searchBySeries(vector<Recipes> allRecipes, vector<string> allSeries, int timeFilter, int difficultyFilter, int sortFilter) {
    vector<Recipes> results;
    string search;
	// get the search string from the user
	// set colour to blue 9
	setColor(9);
    cout << "Enter the series you are looking for: " << endl;
    cout << "To show all series, type 'all'." << endl;

	// get user input (colour to grey 8)
	setColor(8);
    search = readLine(true);
    if (search == "all") {
        // print series
		// set colour to white 7
		setColor(7);
        cout << "Series: " << endl;
        for (int i = 0; i < allSeries.size(); i++) {
            cout << allSeries[i] << endl;
        }
		// get the search string from the user
		// set colour to blue 9
		setColor(9);
        cout << "Enter the series you are looking for: " << endl;

		// get user input (colour to grey 8)
		setColor(8);
        search = readLine(false);
    }
    // lowercase the search string and remove leading and trailing spaces
    transform(search.begin(), search.end(), search.begin(), ::tolower);
    search.erase(0, search.find_first_not_of(" "));
    search.erase(search.find_last_not_of(" ") + 1);

    // Go through all the recipes and check if the search string is in the name
    vector<Recipes> applied = applySetting(allRecipes, timeFilter, difficultyFilter);
    for (int i = 0; i < applied.size(); i++) {
        string series = applied[i].getSeries();

        // lowercase the name of the recipes in the array
        transform(series.begin(), series.end(), series.begin(), ::tolower);

        // check if the search string is in the name of the recipe
        // if it is, add the recipe to the results vector
        if (series.find(search) != string::npos) {
            results.push_back(applied[i]);
        }
    }
    printSettings(timeFilter, difficultyFilter, sortFilter);
    // Check that there are recipes based on the search input
    if (results.size() == 0) {
		// set colour to red
		setColor(4);
        cout << endl << "No recipes found." << endl << endl;
    }
    else {
		//Prints the recipes that contains the search string to the results vector
		// set colour to white 7
		setColor(7);
        cout << endl << "Results for recipes with \"" << search << "\": " << endl << endl;
        for (int i = 0; i < results.size(); i++) {
            cout << results[i].toString() << endl;
        }
    }
    return results;
}



/***************************************************************************************************************************************
 *          Options and main                                                                                                           *
****************************************************************************************************************************************/

/**
 * Function to display the options for the user
 * Takes the user input and calls the appropriate function
*/
 void options(RealmOfRecipes& app) {

    //set colour to blue
	setColor(3);

    // display the options
    printf("1. Display all recipes\n");
    printf("2. Search for a recipe\n");
    printf("3. Search recipes by series\n");
    printf("4. Search by ingredient\n");
    printf("5. Set Settings\n");
    printf("6. Random recipe\n");
    printf("7. Quit\n");

	// get the user choice (colour to grey 8)
	setColor(8);

    int choice;
    cin >> choice;

    // call the appropriate function based on the user choice
    if (choice == 1) {
		// display all recipes (white 7)
		setColor(7);
        display(app.allRecipes);
    }
    else if (choice == 2) {
        searchByName(app.allRecipes);
    }
    else if (choice == 3) {
        searchBySeries(app.allRecipes, app.allSeries, app.timeFilter,app.difficultyFilter, app.sortFilter);
    }
    else if (choice == 4) {
        searchByIngredient(app.allRecipes, app.timeFilter, app.difficultyFilter, app.sortFilter);
    }
    else if (choice == 5) {
        setSettings(app);
    }
    else if (choice == 6) {
        random(app.allRecipes, app.timeFilter, app.difficultyFilter, app.sortFilter);
    }
    else if (choice == 7) {
		// set colour to magenta
		setColor(5);
        quit();
    }
    else {
        // if invalid choice
		//set colour to red
		setColor(4);
        cout << "Invalid choice. Please try again." << endl;
        // reset the cin buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

}