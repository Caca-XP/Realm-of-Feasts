#include "Support.h"


// Function to split a string into a vector of strings
vector<string> split_string(string str, string delimiter, bool lowercase = true) {
    // lowercase the string
    if (lowercase) {
        transform(str.begin(), str.end(), str.begin(), ::tolower);
    }
    vector<string> result;
    size_t pos = 0;
    while ((pos = str.find(delimiter)) != string::npos) {
        string token = str.substr(0, pos);
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


/* Function to print goodbye
*/
void printGoodbye() {
    cout << "Farewell traveler, may our paths cross once more." << endl;
}

/* Function to quit the program
*/
void quit() {
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
    If ignore is true, ignores the newline character left in the input stream from previous input.
    Returns the user input (the whole line of input as string)
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
	if (color < 0 || color > 15) {
		cerr << "The color code you have entered is forbidden: " << color << endl;
		return;
	}
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

/** Function to restrict each line length
* @param str the string to restrict
* @param length the length to restrict the string to
* @param divider the divider for next lines
* @param space the space to add
* @return the restricted string
*/
string restrictLineLength(string str, int length, char divider, int space) {
    // Only attempt to trim quotes if the string is long enough
    if (str.length() > 1 && str.front() == '"' && str.back() == '"') {
        str = str.substr(1, str.length() - 2);
    }

	// Remove leading and trailing spaces
	str.erase(0, str.find_first_not_of(" "));
	str.erase(str.find_last_not_of(" ") + 1);

    // for every length characters after a newline, add a new line at the next space
    int counter = 0;
    for (int i = 0; i < str.length(); i++) {
        if (divider != ' ' && str[i] == divider) {
            counter = 0;
        }
        else {
            counter++;
        }
        if (counter >= length) {
            if (str[i] == ' ') {
				if (space == 0) {
					str.insert(i, "\n");
				}
				else {
					str.insert(i, "\n" + string(space - 1, ' '));
				}
                counter = 0;
            }
        }
    }
	return str;
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
vector<Ingredients> process_ingred(const string& ingred) {

    string ingredients;
    // if the start and end of the string are both " then remove them
    if (ingred.length() > 0 && ingred.front() == '"' && ingred.back() == '"') {
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
                throw out_of_range("The ingredient lacks the necessary magical components.");
            } else {
                ingredients_list.push_back(Ingredients(stod(ingredient_units[0]), ingredient_units[1], ingredient_units[2]));
            }

        }
        catch (const out_of_range& e) {
            cerr << "*******************************************************************************************************\nAn unseen force blocks access to the ingredient parts: " << ingredient << "\nException: " << e.what() << endl;
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
    string instructions = instruct;
	instructions = replaceAll(instructions, "|| ", "||");

	instructions = restrictLineLength(instructions, 100, '|', 3);


    // Replace all occurrences of "||" with newline characters
    instructions = replaceAll(instructions, "||", "\n\n");


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
        cerr << "*******************************************************************************************************\nThe time you have entered does not align with the flow of the realms: " << time_str << "\nException: " << e.what() << endl;
        return -1;
    }
    catch (const out_of_range& e) {
        cerr << "*******************************************************************************************************\nThe time you've entered strays beyond the boundaries of the known realms: " << time_str << "\nException: " << e.what() << endl;
        return -1;
    }
    return time;
}

//Enum of values of the difficulty levels
Level process_difficulty(string difficulty_str) {
    Level difficulty;
	// clean the string
	difficulty_str.erase(0, difficulty_str.find_first_not_of(" "));
	difficulty_str.erase(difficulty_str.find_last_not_of(" ") + 1);
	// lowercase the string
	transform(difficulty_str.begin(), difficulty_str.end(), difficulty_str.begin(), ::tolower);

    if (difficulty_str == "easy") {
        difficulty = Easy;
    }
    else if (difficulty_str == "medium") {
        difficulty = Medium;
    }
    else if (difficulty_str == "hard") {
        difficulty = Hard;
    }
    else {
        cerr << "*******************************************************************************************************\nThe chosen difficulty level does not exist within the realm's trials: " << difficulty_str << endl;
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

		name = restrictLineLength(parts[0], 100, ' ', 6);
		series = restrictLineLength(parts[1], 100, ' ', 8);
		description = restrictLineLength(parts[2], 80, ' ', 13);
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
 vector<Recipes> applySetting(vector<Recipes> currentRecipes, int timeFilter, int difficultyFilter, const vector<string>& excludedIngredients) {

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
        if (excludedIngredients.size() > 0) {
            bool excluded = false;
            vector<string> ingredientsNames = currentRecipes[i].getIngredientsNames();
            // if any of the excluded ingredients are in the recipe, exclude it
            for (int j = 0; j < excludedIngredients.size(); j++) {
                for (int k = 0; k < ingredientsNames.size(); k++) {
                    // if the excluded ingredient is a substring of any ingredient name
                    if (ingredientsNames[k].find(excludedIngredients[j]) != string::npos) {
                        excluded = true;
                        break;
                    }
                }
                if (excluded) {
                    break;
                }
            }
            if (excluded) {
                continue;
            }
        }
        
        results.push_back(currentRecipes[i]);
    }
    if (results.size() == 0) {
		// set colour to red
		setColor(4);

        cout << endl << "No such recipe exists within the forgotten archives." << endl << endl;
    }
    return results;
}

/**
 * Function to print the settings set by the user
*/
 void printSettings(int timeFilter, int difficultyFilter, int sortFilter, const vector<string>& excludedIngredients) {
	// set colour to light yellow
	setColor(14);

    cout << "\nActive selections: \n";
    if (difficultyFilter != 0) {
        if (difficultyFilter == 1) {
			//set colour to green
			setColor(10);
            cout << "Difficulty: Easy \n";
        }
        else if (difficultyFilter == 2) {
			//set colour to yellow
			setColor(6);
            cout << "Difficulty: Medium \n";
        }
        else if (difficultyFilter == 3) {
			//set colour to red
			setColor(12);
            cout << "Difficulty: Hard \n";
        }
    }
    if (timeFilter != 0) {
        if (timeFilter == 1) {
			//set colour to green
			setColor(10);
            cout << "Time: Less than 30 minutes \n";
        }
        else if (timeFilter == 2) {
			//set colour to yellow
			setColor(6);
            cout << "Time: 30 to 60 minutes \n";
        }
        else if (timeFilter == 3) {
			//set colour to red
			setColor(12);
            cout << "Time: More than 60 minutes \n";
        }
    }
    if (difficultyFilter == 0 && timeFilter == 0) {
		// set colour to white
		setColor(15);
        cout << "Naught \n";
    }
	// set colour to light yellow
	setColor(14);
    cout << "Active arrangement: \n";
    if (sortFilter != 0) {
        if (sortFilter == 1) {
			//set colour to light blue
			setColor(11);
            cout << "Sort by difficulty \n";
        }
        else if (sortFilter == 2) {
			//set colour to blue
			setColor(11);
            cout << "Sort by difficulty reverse \n";
        }
        else if (sortFilter == 3) {
			//set colour to light magenta
			setColor(13);
            cout << "Sort by time \n";
        }
        else if (sortFilter == 4) {
			//set colour to magenta
			setColor(13);
            cout << "Sort by time reverse \n";
        }
    }
    else {
		//set colour to white
		setColor(15);
        cout << "Naught \n";
    }
    if (excludedIngredients.size() > 0) {
        //set colour to light red
        setColor(12);
        cout << "Excluded ingredients: ";
        for (int i = 0; i < excludedIngredients.size(); i++) {
            cout << excludedIngredients[i];
            if (i != excludedIngredients.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }

    cout << "\n";
}

 /*
 * Function to set the difficulty filter
  * @param app the RealmOfRecipes object
 */
 void handleDifficultyFilter(RealmOfRecipes& app) {
     while (true) {
         setColor(10); printf("1. Easy\n");
         setColor(6); printf("2. Medium\n");
         setColor(12); printf("3. Hard\n");
         setColor(15); printf("4. Return to the previous chapter\n");

         int difficultyChoice;
         cin >> difficultyChoice;

         if (difficultyChoice >= 1 && difficultyChoice <= 3) {
             app.difficultyFilter = difficultyChoice;
             break;
         }
         else if (difficultyChoice == 4) break;
         else showInvalidChoiceMessage();
     }
 }

 /**
  * Function to handle the time filter
  * @param app the RealmOfRecipes object
  */
 void handleTimeFilter(RealmOfRecipes& app) {
     while (true) {
         setColor(10); printf("1. Less than 30 minutes\n");
         setColor(6); printf("2. 30 to 60 minutes\n");
         setColor(12); printf("3. More than 60 minutes\n");
         setColor(15); printf("4. Return to the previous chapter\n");

         int timeChoice;
         cin >> timeChoice;

         if (timeChoice >= 1 && timeChoice <= 3) {
             app.timeFilter = timeChoice;
             break;
         }
         else if (timeChoice == 4) break;
         else showInvalidChoiceMessage();
     }
 }

 /**
  * Function to handle the sort
  * @param app the RealmOfRecipes object
  */
 void handleSort(RealmOfRecipes& app) {
     while (true) {
         setColor(11); printf("1. Sort by difficulty\n");
         setColor(11); printf("2. Sort by difficulty reverse\n");
         setColor(13); printf("3. Sort by time\n");
         setColor(13); printf("4. Sort by time reverse\n");
         setColor(15); printf("5. Return to the previous chapter\n");

         int sortChoice;
         cin >> sortChoice;

         if (sortChoice == 1 || sortChoice == 2) {
             sort(app.allRecipes.begin(), app.allRecipes.end(), sortByDifficulty);
             if (sortChoice == 2) reverse(app.allRecipes.begin(), app.allRecipes.end());
             app.sortFilter = sortChoice;
             break;
         }
         else if (sortChoice == 3 || sortChoice == 4) {
             sort(app.allRecipes.begin(), app.allRecipes.end(), sortByTime);
             if (sortChoice == 4) reverse(app.allRecipes.begin(), app.allRecipes.end());
             app.sortFilter = sortChoice;
             break;
         }
         else if (sortChoice == 5) break;
         else showInvalidChoiceMessage();
     }
 }


 /**
  * Function to handle the excluded ingredients
  * @param app the RealmOfRecipes object
  */
 void handleExcludedIngredients(RealmOfRecipes& app) {
     while (true) {
        // print the excluded ingredients
        setColor(12); printf("Excluded ingredients: ");
        for (int i = 0; i < app.excludedIngredients.size(); i++) {
            cout << app.excludedIngredients[i];
            if (i != app.excludedIngredients.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl << endl;

        // Ask to add, or clear, or remove
        setColor(10); printf("1. Add excluded ingredients\n");
        setColor(6); printf("2. Clear excluded ingredients\n");
        setColor(12); printf("3. Remove excluded ingredients\n");
        setColor(15); printf("4. Return to the previous chapter\n");

        int excludedChoice;
        cin >> excludedChoice;

        if (excludedChoice == 1) {
            setColor(10); printf("Enter the ingredients you wish to exclude (separated by commas): ");
            string excludedIngredients = readLine(true);
            vector<string> excluded = split_string(excludedIngredients, ",");
            app.excludedIngredients.insert(app.excludedIngredients.end(), excluded.begin(), excluded.end());
            // sort the excluded ingredients
            sort(app.excludedIngredients.begin(), app.excludedIngredients.end());
            break;
        }
        else if (excludedChoice == 2) {
            app.excludedIngredients.clear();
            break;
        }
        else if (excludedChoice == 3) {
            setColor(12); printf("Enter the ingredients you wish to remove (separated by commas): ");
            string removeIngredients = readLine(true);
            vector<string> remove = split_string(removeIngredients, ",");
            for (int i = 0; i < remove.size(); i++) {
                vector<string>::iterator it = find(app.excludedIngredients.begin(), app.excludedIngredients.end(), remove[i]);
                if (it != app.excludedIngredients.end()) {
                    app.excludedIngredients.erase(it);
                }
            }
            break;
        }
        else if (excludedChoice == 4) break;
        else showInvalidChoiceMessage();
     }
 }

 /**
  * Function to display an invalid choice message
  */
 void showInvalidChoiceMessage() {
     setColor(4);
     cout << "An unwise choice has been made. Seek another path." << endl;
     cin.clear();
     cin.ignore(numeric_limits<streamsize>::max(), '\n');
 }

/**
 * Function to set settings for the recipes
 * User can set filters for difficulty and time
 * User can set sorting for the recipes
*/
 void setSettings(RealmOfRecipes& app) {
	 bool exitMenu = false;

     while (!exitMenu) {
         printSettings(app.timeFilter, app.difficultyFilter, app.sortFilter, app.excludedIngredients);
         
         setColor(3);
         printf("1. Filter by difficulty\n");
         printf("2. Filter by time\n");
         printf("3. Reset filters\n");
         printf("4. Set sort\n");
         printf("5. Reset sort\n");
         printf("6. Set banned ingredients\n");
         printf("7. Return to the previous chapter\n");

         int filterChoice;
         cin >> filterChoice;

         switch (filterChoice) {
             case 1: handleDifficultyFilter(app); break;
             case 2: handleTimeFilter(app); break;
             case 3: app.timeFilter = 0; app.difficultyFilter = 0; break;
             case 4: handleSort(app); break;
             case 5: app.sortFilter = 0; break;
             case 6: handleExcludedIngredients(app); break;
			 case 7: exitMenu = true; break;
             default: showInvalidChoiceMessage(); break;
         }
     }

     while (true) {
         setColor(3);
         printf("1. Record settings and unveil all recipes with the chosen enchantments\n");
         printf("2. Record settings and return to the previous chapter\n");

         int applyChoice;
         cin >> applyChoice;

         if (applyChoice == 1) {
             vector<Recipes> applied = applySetting(app.allRecipes, app.timeFilter, app.difficultyFilter, app.excludedIngredients);
             setColor(7);
             display(applied);
             break;
         }
         else if (applyChoice == 2) {
             setColor(2);
             printf("Settings recorded.\n\n");
             break;
         }
         else {
             showInvalidChoiceMessage();
         }
     }
 }



/**
 * Function that displays a random recipe within the allRecipes array
*/
 void random(const vector<Recipes>& allRecipes, int timeFilter, int difficultyFilter, int sortFilter, const vector<string>& excludedIngredients) {
    // Check if recipes vector is empty
    if (allRecipes.empty()) {
        // set colour to red for the message
        setColor(4);
        cout << "No recipes align with your search." << endl;
        return; // Exit the function
    }

    vector<Recipes> applied = applySetting(allRecipes, timeFilter, difficultyFilter, excludedIngredients);

	if (applied.size() == 0) {
        return;
	}

    int randomIndex = rand() % applied.size();
    printSettings(timeFilter, difficultyFilter, sortFilter, excludedIngredients);
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
    cout << "Speak of the name of the recipe you seek: ";

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
        cout << endl << "Oh woe, no recipes of such name dwell within these scrolls." << endl << endl;
    }
    else {
		//Prints the recipes that contains the search string to the results vector
		// set colour to white 7
		setColor(7);
        cout << endl << "Behold the recipes with \"" << search << "\": " << endl << endl;
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
 vector<Recipes> searchByIngredient(const vector<Recipes>& allRecipes, int timeFilter, int difficultyFilter, int sortFilter, const vector<string>& excludedIngredients) {
    vector<Recipes> results;
    string search;

	// get the search string from the user
	// set colour to blue 9
	setColor(9);
    cout << "State the magical ingredients you seek (separate them by commas): ";

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
    vector<Recipes> applied = applySetting(allRecipes, timeFilter, difficultyFilter, excludedIngredients);
    for (int i = 0; i < applied.size(); i++) {
        vector<string> ingredients = applied[i].getIngredientsNames();
        // use double pointer to check if all the search ingredients are in the recipe ingredients
        if (includes(ingredients.begin(), ingredients.end(), searchIngredients.begin(), searchIngredients.end())) {
            results.push_back(applied[i]);
        }

    }
    printSettings(timeFilter, difficultyFilter, sortFilter, excludedIngredients);
    if (results.size() == 0) {
		// set colour to red
		setColor(4);
        cout << endl << "Regrettably, no recipes could be conjured with those ingredients." << endl << endl;
    }
    else {
        //Prints the recipes that contains the search string to the results vector
		// set colour to white 7
		setColor(7);
        cout << endl << "Behold the recipes containing the ingredients '" << search << "': " << endl << endl;
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
 vector<Recipes> searchBySeries(const vector<Recipes>& allRecipes, const vector<string>& allSeries, int timeFilter, int difficultyFilter, int sortFilter, const vector<string>& excludedIngredients) {
    vector<Recipes> results;
    string search;
	// get the search string from the user
	// set colour to blue 9
	setColor(9);
    cout << "Name the fable you seek: " << endl;
    cout << "To unveil all fables (series), simply utter 'all'." << endl;

	// get user input (colour to grey 8)
	setColor(8);
    search = readLine(true);
    if (search == "all") {
        // print series
		// set colour to white 7
		setColor(7);
        cout << "Fables of legend:" << endl;
        for (int i = 0; i < allSeries.size(); i++) {
            cout << allSeries[i] << endl;
        }
		// get the search string from the user
		// set colour to blue 9
		setColor(9);
        cout << "Speak the name of the fable you wish to explore: " << endl;

		// get user input (colour to grey 8)
		setColor(8);
        search = readLine(false);
    }
    // lowercase the search string and remove leading and trailing spaces
    transform(search.begin(), search.end(), search.begin(), ::tolower);
    search.erase(0, search.find_first_not_of(" "));
    search.erase(search.find_last_not_of(" ") + 1);

    // Go through all the recipes and check if the search string is in the name
    vector<Recipes> applied = applySetting(allRecipes, timeFilter, difficultyFilter, excludedIngredients);
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
    printSettings(timeFilter, difficultyFilter, sortFilter, excludedIngredients);
    // Check that there are recipes based on the search input
    if (results.size() == 0) {
		// set colour to red
		setColor(4);
        cout << endl << "Alas, no recipes were discovered in this fable." << endl << endl;
    }
    else {
		//Prints the recipes that contains the search string to the results vector
		// set colour to white 7
		setColor(7);
        cout << endl << "Behold the recipes found for your search of \"" << search << "\": " << endl << endl;
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
    printf("1. Reveal the entire archive of recipes\n");
    printf("2. Seek out a recipe by name\n");
    printf("3. Search through the chronicles of a specific fable (series)\n");
    printf("4. Hunt for recipes by mystical ingredients\n");
    printf("5. Tinker with the magical settings\n");
    printf("6. Let fate decide - summon a random recipe\n");
    printf("7. End your quest\n");

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
        searchBySeries(app.allRecipes, app.allSeries, app.timeFilter,app.difficultyFilter, app.sortFilter, app.excludedIngredients);
    }
    else if (choice == 4) {
        searchByIngredient(app.allRecipes, app.timeFilter, app.difficultyFilter, app.sortFilter, app.excludedIngredients);
    }
    else if (choice == 5) {
        setSettings(app);
    }
    else if (choice == 6) {
        random(app.allRecipes, app.timeFilter, app.difficultyFilter, app.sortFilter, app.excludedIngredients);
    }
    else if (choice == 7) {
		// set colour to magenta
		setColor(5);
        quit();
    }
    else {
        // if invalid choice
        showInvalidChoiceMessage();
    }

}

/**
* Function to check with the user to continue and clear the command-line screen.
* Takes the user input using std::cin and calls the system clear.
*/
void clearScreen() {
    setColor(9);  // Assuming setColor is defined elsewhere
    std::cout << "\nPress any key to continue... " << std::endl;

    // Clear any leftover characters from the input buffer
    std::cin.clear();                      // Clear any error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Discard any leftover input

    // Now wait for the user to provide input (including just pressing Enter)
    std::string dummyInput;
    std::getline(std::cin, dummyInput);    // Wait for any user input

    system("cls");  // Clear the screen (use "clear" instead of "cls" on Linux/macOS)
}
