/**
 * Application for Unit Testing the Constructor of Recipes
 * @see Recipes.h
 * @see App.cpp
 * @author Mythical Cooks
 */
#include <assert.h>
#include "Recipes.h"
#include <algorithm>

enum Level {
    Easy = 1,
    Medium = 2,
    Hard = 3
};

    /**Implementation of Recipes functions */
    /*Default Constructor */
    Recipes::Recipes(){
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
        @return ingredients of the recipe as a vector
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

    /**
     * @test Default Constructor test
     */
    void testDefaultConstructor(){
        Recipes def = Recipes();
        // Check if the default constructor sets the values to the correct default values
        assert(def.getName() == "");
        assert(def.getDescription() == "");
        assert(def.getIngredients().size() == 0);
        assert(def.getInstructions() == "");
        assert(def.getTime() == 0);
        assert(def.getDifficulty() == 0);
    }

    /**
     * @test Defined Constructor test
     */
    void testDefinedConstructor(){
        Recipes def = Recipes("name", "series", "description", "ing1, ing2, ing3", "instructions", 10, Easy);
        // Check if the defined constructor sets the values to the correct values
        assert(def.getName() == "name");
        assert(def.getDescription() == "description");
        assert(def.getIngredients().size() == 3);
        assert(def.getInstructions() == "instructions");
        assert(def.getTime() == 10);
        assert(def.getDifficulty() == Easy);

        // Checks comparison between two defined constructors
        Recipes def2 = Recipes("name", "series", "description", "ing1, ing2, ing3, ing4", "instructions", 10, Medium);
        assert(def2.getIngredients().size() != def.getIngredients().size());
        assert(def2.getDifficulty() != def.getDifficulty());
        assert(def2.getDifficulty() == Medium);
        assert(def2.getTime() == def.getTime());
        assert(def2.getName() == def.getName());

    }

    /**
     * @test Split String test - tests the split_string function 
     * to see if it correctly splits a string into a vector of strings, ignoring blank spaces divided by commas
     */
    void testSplitString(){
        //
        vector<string> test = split_string("ing1, ing2, ing3", ", ");
        assert(test.size() == 3);
        assert(test[0] == "ing1");
        assert(test[1] == "ing2");
        assert(test[2] == "ing3");

        vector<string> test2 = split_string("ing1,    Cheese, ONION, ing4", ", ");
        assert(test2.size() == 4);
        assert(test2[0] == "ing1");
        assert(test2[1] == "cheese");
        assert(test2[2] == "onion");
        assert(test2[3] == "ing4");

        vector<string> test3 = split_string("ing1,   ing2, Cow, ing4, ing5", ", ");
        assert(test3.size() == 5);
        assert(test3[0] == "ing1");
        assert(test3[1] == "ing2");
        assert(test3[2] != "ing3");
        assert(test3[3] == "ing4");
        assert(test3[4] == "ing5");
        assert(test3.size() != 6);
    }

    /**
     * @test accessor methods
     */
    void testAccessors(){
        string nm = "name";
        string ser = "series";
        string desc = "description";
        string ing = "ing1, ing2, ing3";
        string ins = "instructions";
        int t = 10;
        enum Level lv = Easy;

        Recipes def = Recipes(nm, ser, desc, ing, ins, t, lv);
        assert(def.getName() == nm);
        assert(def.getDescription() == desc);
        assert(def.getIngredients().size() == 3);
        assert(def.getInstructions() == ins);
        assert(def.getTime() == t);
        assert(def.getDifficulty() == lv);

        nm = "name2";
        ser = "series2";
        desc = "description2";
        ing = "ing1, ing2, ing3, ing4";
        ins = "instructions2";
        t = 20;
        lv = Medium;

        assert(def.getName() != nm);
        assert(def.getDescription() != desc);
        assert(def.getIngredients().size() != ing.size());
        assert(def.getInstructions() != ins);
        assert(def.getTime() != t);
        assert(def.getDifficulty() != lv);

    }


    int main(){
        testDefaultConstructor();
        testDefinedConstructor();
        testSplitString();
        testAccessors();

        return 0;
    }
    