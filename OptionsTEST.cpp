/**
 * Application for Unit Testing the Option menu of the App
 * @see App.cpp
 * @author Mythical Cooks
 */
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <array>
#include "Recipes.h"

using namespace std;

string option;



/* Function to display the options for the user
    Takes the user input and calls the appropriate function
*/
void options(int specifiedOption, int specifiedSortChoice){
    /* Uneeded in testing code
    // display the options
    printf("1. Display all recipes\n");
    printf("2. Search for a recipe\n");
    printf("3. Sort recipes\n");
    printf("4. Filter recipes by series\n");
    printf("5. Search by ingredient\n");
    printf("6. Random recipe\n");
    printf("7. Quit\n");
    */

    // get the user choice
    int choice = specifiedOption;
    //cin >> choice;

    // call the appropriate function based on the user choice
    if (choice == 1){
        option = "displaying";
    }
    else if (choice == 2){
        option = "searching by name";
    }
    else if (choice == 3){
        while (true){
            /* Uneeded in testing code
            // display the sort options
            printf("1. Sort by difficulty\n");
            printf("2. Sort by time\n");
            printf("3. Back\n");
            */

            // get the user choice
            int sortChoice = specifiedSortChoice;
            //cin >> sortChoice;

            // call the appropriate sort function based on the user choice
            if (sortChoice == 1){
                option = "sorting by difficulty";
                option += "+ displaying";
                break;
            }
            else if (sortChoice == 2){
                option = "sorting by time";
                option += "+ displaying";
                break;
            }
            else if (sortChoice == 3){
                option = "back";
                break;
            }
            else{
                // if invalid choice
                cout << "Invalid choice. Please try again." << endl;
                option = "invalid";
                // reset the cin buffer
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    else if (choice == 4){
        option = "filtering by series";
    }
    else if (choice == 5){
        option = "searching by ingredient";
    }
    else if (choice == 6){
        option = "displaying";
    }
    else if (choice == 7){
        option = "quitting";
    }
    else{
        // if invalid choice
        //cout << "Invalid choice. Please try again." << endl;
        option = "invalid";
        /* Uneded in testing code
        // reset the cin buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        */
    }
}   

    /**
     * @test Unit test for the Base options function
     */
    void testBaseOptions(){
        // Test case 1
        options(1, 0);
        assert(option == "displaying");

        // Test case 2
        options(2, 0);
        assert(option == "searching by name");

        // Test case 4
        options(4, 0);
        assert(option == "filtering by series");

        // Test case 5
        options(5, 0);
        assert(option == "searching by ingredient");

        // Test case 6
        options(6, 0);
        assert(option == "displaying");

        // Test case 7
        options(7, 0);
        assert(option == "quitting");

        // Test case 8
        options(8, 0);
        assert(option == "invalid");
    }

    /**
     * @test Unit test for the Sort options function
     * With nested options
     */
    void testSortOptions(){
        // Test case 1
        options(3, 1);
        assert(option == "sorting by difficulty+ displaying");

        // Test case 2
        options(3, 2);
        assert(option == "sorting by time+ displaying");

        // Test case 3
        options(3, 3);
        assert(option == "back");
    }

    int main(){
        testBaseOptions();
        testSortOptions();
        return 0;
    }
