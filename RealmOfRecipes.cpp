
#include "RealmOfRecipes.h"

/**
 * Default constructor
 */
RealmOfRecipes::RealmOfRecipes()
    : timeFilter(0), difficultyFilter(0), sortFilter(0), allRecipes({}), allSeries({}), excludedIngredients({}) {}

/**
 * Parameterized constructor
 */
RealmOfRecipes::RealmOfRecipes(const vector<Recipes>& recipes, int time, int difficulty, int sort, const vector<string>& series, const vector<string>& excluded)
    : timeFilter(time), difficultyFilter(difficulty), sortFilter(sort), allRecipes(recipes), allSeries(series), excludedIngredients(excluded) {}

/**
 * Destructor
 */

RealmOfRecipes::~RealmOfRecipes(){
}
