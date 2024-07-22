# include <iostream>
# include <string>
# include <fstream>
# include "Recipes.h" // Include the header file that contains the definition of the 'Recipes' class

using namespace std;

/*Default Constructor */
    Recipes::Recipes(){
    };

    /*Defined Constructor*/
    Recipes::Recipes(string nm, string ser, string desc, string ing, string ins, string t, string lv) {
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
    string Recipes::getTime() {
        return time;
    }

    /* Accessor function to get the difficulty of the recipe
    */
    string Recipes::getDifficulty() {
        return difficulty;
    }



/// @todo find number of recipes in data
const int numRecipes = 1;

Recipes pasta = Recipes("Pasta", "Italian", "A simple pasta recipe", "Pasta, Tomato Sauce, Cheese", "Boil pasta, add sauce, add cheese", "30 minutes", "Easy");

Recipes allRecipes[numRecipes];

void setup(){
// read file and initialise allRecipes
    allRecipes[0] = Recipes("Pasta", "Italian", "A simple pasta recipe", "Pasta, Tomato Sauce, Cheese", "Boil pasta, add sauce, add cheese", "30 minutes", "Easy");
}

void display(Recipes recipes[]){
    int length = sizeof(recipes) / sizeof(Recipes);
    for (int i = 0; i < length; i++){
        cout << recipes[i].getName() << endl;
    }
}



void quit(){
    cout << "Goodbye!" << endl;
    exit(0);
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
        // sort();
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
    options();

    // 
    return 0;
}