# include "App.h" // Include the header file that contains the definition of the 'App' class


/* App class for the realm of feast Recipe finder app
   Contains the implementation of the functions of Recipes Class (Recipes.h)

   @version 1.0
   @author Cooks Hello
*/


/** Main function to run the program
 * Calls the setup function to initialise the data
 * Calls the options function to display the options for the user
*/
int main() {
    RealmOfRecipes app = RealmOfRecipes();
    
    // read and initialize the data for recipes
    setup("RecipesTest.txt", app.app_allRecipes, app.app_allSeries);//change to database later

    std::cout << "Welcome to the Realm of Feasts!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Delay for 500 milliseconds

    // set colour to purple
	setColor(5);

    std::cout << "A recipe finder app to fix your fictional food craving." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(900)); 

    std::cout << "Using the options below, go on a quest to find the perfect recipe for your feast." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1100)); 

    std::cout << "All recipes shall be from the wondrous fictional worlds of Harry Potter, Studio Ghibli, and many more!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1200)); 

    std::cout << "All you have to do is enter a number to interact with the App" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1400)); 

    std::cout << "Good luck!" << std::endl << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1600)); 
    
    while (true) {
        options(app.app_allRecipes, app.app_allSeries, app.app_timeFilter, app.app_difficultyFilter, app.app_sortFilter);
    }

    return 0;
}