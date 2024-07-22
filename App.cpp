# include <iostream>
# include <string>
# include <fstream>
# include "Recipes.h" // Include the header file that contains the definition of the 'Recipes' class
# include <array>
# include <algorithm>

using namespace std;

enum Level {
    Easy = 1,
    Medium = 2,
    Hard = 3
};


/*Default Constructor */
    Recipes::Recipes(){
    };

    /*Defined Constructor*/
    Recipes::Recipes(string nm, string ser, string desc, string ing, string ins, int t, enum Level lv) {
        name = nm;
        series = ser;
        description = desc;
        ingredients = ing;
        instructions = ins;
        time = t;
        difficulty = lv;

        
    }

    /*Destructor code (idk what this is for)*/
    Recipes::~Recipes() {
        // Destructor code here
    }

    /* Accessor function to get the name of the recipe
    */
    string Recipes::getName() {
        return name;
    }

    /* Accessor function to get the description of the recipe
    */
    string Recipes::getDescription() {
        return description;
    }

    /* Accessor function to get the ingredients of the recipe
    */
    string Recipes::getIngredients() {
        return ingredients;
    }

    /* Accessor function to get the instructions of the recipe
    */
    string Recipes::getInstructions() {
        return instructions;
    }

    /* Accessor function to get the time of the recipe
    */
    int Recipes::getTime() {
        return time;
    }

    /* Accessor function to get the difficulty of the recipe
    */
    enum Level Recipes::getDifficulty() {
        return difficulty;
    }

    /* Function to return a string representation of the recipe
    */
    string Recipes::toString() {
        string result = "Name: " + name + "\n";
        result += "Series: " + series + "\n";
        result += "Description: " + description + "\n";
        result += "Ingredients: " + ingredients + "\n";
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



/// @todo find number of recipes in data
const int numRecipes = 5;

Recipes pasta = Recipes("Pasta", "Italian", "A simple pasta recipe", "Pasta, Tomato Sauce, Cheese", "Boil pasta, add sauce, add cheese", 30, Easy);

array<Recipes, numRecipes> allRecipes;

void setup(){
// read file and initialise allRecipes
    allRecipes[0] = Recipes("Pasta", "Italian", "A simple pasta recipe", "Pasta, Tomato Sauce, Cheese", "Boil pasta, add sauce, add cheese", 30, Easy);
    allRecipes[1] = Recipes("Pizza", "Italian", "A simple pizza recipe", "Pizza Dough, Tomato Sauce, Cheese", "Roll dough, add sauce, add cheese", 45 , Medium);
    allRecipes[2] = Recipes("Burger", "American", "A simple burger recipe", "Burger Patty, Bun, Lettuce, Tomato, Cheese", "Cook patty, assemble burger", 20 , Easy);
    allRecipes[3] = Recipes("Sushi", "Japanese", "A simple sushi recipe", "Rice, Fish, Seaweed", "Cook rice, add fish, wrap in seaweed", 60 , Hard);
    allRecipes[4] = Recipes("Curry", "Indian", "A simple curry recipe", "Curry Paste, Meat, Vegetables", "Cook meat, add vegetables, add paste", 45 , Medium);
}

void display(array<Recipes, numRecipes> recipes){
    for (int i = 0; i < recipes.size(); i++){
        cout << recipes[i].toString() << endl;
    }
}


void quit(){
    cout << "Goodbye!" << endl;
    exit(0);
}


bool sortByDifficulty(Recipes a, Recipes b){
    return a.getDifficulty() < b.getDifficulty();
}

bool sortByTime(Recipes a, Recipes b){
    return a.getTime() < b.getTime();
}



void options(){
    printf("1. Display all recipes\n");
    printf("2. Search for a recipe\n");
    printf("3. Sort recipes\n");
    printf("4. Filter recipes\n");
    printf("5. Search by ingredient\n");
    printf("6. Random recipe\n");
    printf("7. Quit\n");
    int choice;
    cin >> choice;
    if (choice == 1){
        display(allRecipes);
    }
    else if (choice == 2){
        // search();
    }
    else if (choice == 3){
        while (true){
            printf("1. Sort by difficulty\n");
            printf("2. Sort by time\n");
            printf("3. Back\n");
            int sortChoice;
            cin >> sortChoice;
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
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }
    else if (choice == 4){
        // filter();
    }
    else if (choice == 5){
        // searchByIngredient();
    }
    else if (choice == 6){
        // random();
    }
    else if (choice == 7){
        quit();
    }
    else{
        cout << "Invalid choice. Please try again." << endl;
    }

}


int main(){
    // read and initialize the data for recipes
    setup();
    while (true){
        options();
    }
    // 
    return 0;
}