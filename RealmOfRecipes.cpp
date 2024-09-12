
#include "RealmOfRecipes.h"

/**
 * Default constructor
 */
RealmOfRecipes::RealmOfRecipes(){
    app_allRecipes = {};
    app_timeFilter = 0;
    app_difficultyFilter = 0;
    app_sortFilter = 0;
    app_allSeries = {};
}

/**
 * Parameterized constructor
 */
RealmOfRecipes::RealmOfRecipes(vector<Recipes> allRecipes, int timeFilter, int difficultyFilter, int sortFilter, vector<string> allSeries){
    app_allRecipes = allRecipes;
    app_timeFilter = timeFilter;
    app_difficultyFilter = difficultyFilter;
    app_sortFilter = sortFilter;
    app_allSeries = allSeries;
}

/**
 * Destructor
 */

RealmOfRecipes::~RealmOfRecipes(){
}

/**
 * Function to update all recipes
 */
void RealmOfRecipes::updateAllRecipes(vector<Recipes> allRecipes){
    app_allRecipes = allRecipes;
}

/**
 * Function to update the time filter
 */
void RealmOfRecipes::updateTimeFilter(int timeFilter){
    app_timeFilter = timeFilter;
}


/**
 * Function to update the difficulty filter
 */
void RealmOfRecipes::updateDifficultyFilter(int difficultyFilter){
    app_difficultyFilter = difficultyFilter;
}

/**
 * Function to update the sort filter
 */
void RealmOfRecipes::updateSortFilter(int sortFilter){
    app_sortFilter = sortFilter;
}

/**
 * Function to update all series
 */
void RealmOfRecipes::updateAllSeries(vector<string> allSeries){
    app_allSeries = allSeries;
}