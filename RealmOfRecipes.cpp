
#include "RealmOfRecipes.h"

/**
 * Default constructor
 */
RealmOfRecipes::RealmOfRecipes(){
    allRecipes = {};
    timeFilter = 0;
    difficultyFilter = 0;
    sortFilter = 0;
    allSeries = {};
}

/**
 * Parameterized constructor
 */
RealmOfRecipes::RealmOfRecipes(vector<Recipes> recipes, int time, int difficulty, int sort, vector<string> series){
    allRecipes = recipes;
    timeFilter = time;
    difficultyFilter = difficulty;
    sortFilter = sort;
    allSeries = series;
}

/**
 * Destructor
 */

RealmOfRecipes::~RealmOfRecipes(){
}
