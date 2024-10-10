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
    setup("RecipesTest.txt", app);//change to database later

    //std::cout << "Welcome, brave traveler, to the Realm of Feasts!" << std::endl;
    std::cout << R"( 
 __          __  _                            
 \ \        / / | |                           
  \ \  /\  / /__| | ___ ___  _ __ ___   ___   
   \ \/  \/ / _ \ |/ __/ _ \| '_ ` _ \ / _ \  
    \  /\  /  __/ | (_| (_) | | | | | |  __/_ 
     \/  \/ \___|_|\___\___/|_| |_| |_|\___( )
                                           |/ 
                                              )" << '\n';         
std::cout << R"(  
  ____                        _______                  _ _           
 |  _ \                      |__   __|                | | |          
 | |_) |_ __ __ ___   _____     | |_ __ __ ___   _____| | | ___ _ __ 
 |  _ <| '__/ _` \ \ / / _ \    | | '__/ _` \ \ / / _ \ | |/ _ \ '__|
 | |_) | | | (_| |\ V /  __/    | | | | (_| |\ V /  __/ | |  __/ |_  
 |____/|_|  \__,_| \_/ \___|    |_|_|  \__,_| \_/ \___|_|_|\___|_( ) 
                                                                 |/  
                                                                     )" << '\n';
std::cout << R"(   
  _          _   _            _____            _                    __   ______             _       _ 
 | |        | | | |          |  __ \          | |                  / _| |  ____|           | |     | |
 | |_ ___   | |_| |__   ___  | |__) |___  __ _| |_ __ ___     ___ | |_  | |__ ___  __ _ ___| |_ ___| |
 | __/ _ \  | __| '_ \ / _ \ |  _  // _ \/ _` | | '_ ` _ \   / _ \|  _| |  __/ _ \/ _` / __| __/ __| |
 | || (_) | | |_| | | |  __/ | | \ \  __/ (_| | | | | | | | | (_) | |   | | |  __/ (_| \__ \ |_\__ \_|
  \__\___/   \__|_| |_|\___| |_|  \_\___|\__,_|_|_| |_| |_|  \___/|_|   |_|  \___|\__,_|___/\__|___(_)
)" << '\n';
                                                                     
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Delay for 500 milliseconds

    // set colour to purple
	setColor(5);

    std::cout << "A magical recipe quest awaits you, where only the finest dishes from legendary lands can satisfy your craving for the extraordinary." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(900)); 

    std::cout << "With the enchanted choices before you, embark on a journey to discover the perfect recipe for your grand feast." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1100)); 

    std::cout << "Unearth mystical recipes from the fabled worlds of Harry Potter, the enchanted realms of Studio Ghibli, and countless other tales of wonder!" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1200)); 

    std::cout << "Simply invoke the magic of numbers to interact with this wondrous App and begin your culinary adventure." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1400)); 

    std::cout << "May fortune guide your quest!" << std::endl << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1600)); 
    
    while (true) {
        options(app);
    }

    return 0;
}