
#include "RealmOfRecipes.h"

/**
 * Default constructor
 */
RealmOfRecipes::RealmOfRecipes()
    : timeFilter(0), difficultyFilter(0), sortFilter(0), allRecipes({}), allSeries({}) {}

/**
 * Parameterized constructor
 */
RealmOfRecipes::RealmOfRecipes(const vector<Recipes>& recipes, int time, int difficulty, int sort, const vector<string>& series)
    : timeFilter(time), difficultyFilter(difficulty), sortFilter(sort), allRecipes(recipes), allSeries(series) {}

/**
 * Destructor
 */

RealmOfRecipes::~RealmOfRecipes(){
}
