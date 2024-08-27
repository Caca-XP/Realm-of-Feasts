
# include "Recipes.h" // Include the header file that contains the definition of the 'Recipes' class


/***************************************************************************************************************************************
 *          Recipes Class                                                                                                              *
****************************************************************************************************************************************/

/**Implementation of Recipes functions */
/*Default Constructor */
Recipes::Recipes() {
    time = 0;
    difficulty = Level(0);
};

/*Defined Constructor*/
Recipes::Recipes(string nm, string ser, string desc, vector<Ingredients> ing, string ins, int t, enum Level lv) 
    :name(nm), series(ser), description(desc), ingredients(ing), instructions(ins), time(t), difficulty(lv), 
    ingredients_str([&ing]() {
    string result;
    for (int i = 0; i < ing.size(); i++) {
        result += "- " + ing[i].toString();
        if (i != ing.size() - 1) {
            result += "\n";
        }
    }
    return result;
        }()),
    ingredient_names([&ing]() {
    vector<string> names;
    for (int i = 0; i < ing.size(); i++) {
        string ingredient_name = ing[i].getName();
        // make lowercase and remove leading and trailing spaces
        transform(ingredient_name.begin(), ingredient_name.end(), ingredient_name.begin(), ::tolower);
        ingredient_name.erase(0, ingredient_name.find_first_not_of(" "));
        ingredient_name.erase(ingredient_name.find_last_not_of(" ") + 1);

        names.push_back(ingredient_name);
    }
    sort(names.begin(), names.end());
    return names;
        }())
{}

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
vector<Ingredients> Recipes::getIngredients() {
    return ingredients;
}

/* Accessor function to get the ingredients of the recipe
    @return ingredients of the recipe (list)
*/
vector<string> Recipes::getIngredientsNames() {
    return ingredient_names;
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
    result += "Time: " + to_string(time) + " minutes\n";
    result += "Difficulty: ";
    if (difficulty == 1) {
        result += "Easy\n";
    }
    else if (difficulty == 2) {
        result += "Medium\n";
    }
    else if (difficulty == 3) {
        result += "Hard\n";
    }

    result += "Description: " + description + "\n";
    result += "Ingredients: \n" + ingredients_str + "\n";
    result += "Instructions: \n" + instructions + "\n";

    return result;
}

/*Function to return a string of the recipe name, series, time, and difficulty
    @return string of the recipe name, series, time, and difficulty
*/
string Recipes::toStringShort() {
    string result = name + " (" + series + ") - " + to_string(time) + " minutes - ";
    if (difficulty == 1) {
        result += "Easy";
    }
    else if (difficulty == 2) {
        result += "Medium";
    }
    else if (difficulty == 3) {
        result += "Hard";
    }
    return result;
}

