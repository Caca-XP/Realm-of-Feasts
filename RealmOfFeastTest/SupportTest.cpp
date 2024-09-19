#include "pch.h"
#include "CppUnitTest.h"
#include "../Support.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RealmOfFeastTest
{
	TEST_CLASS(SupportTest)
	{/**
		 * Test the methods of the Support.pp
		 * split_string and replaceAll
		 * @see Support.cpp
		 * @test
		 */
		TEST_METHOD(TestSupportFunctions)
		{
			//test the split_string function
			std::string testString = "test1, test2, test3";
			std::string delimiter = ", ";
			vector<string> expectedVector = { "test1", "test2", "test3" };
			vector<string> actualVector = split_string(testString, delimiter, true);

			//Test
			Assert::AreEqual(actualVector.at(0), expectedVector.at(0));
			Assert::AreEqual(actualVector.at(1), expectedVector.at(1));
			Assert::AreEqual(actualVector.at(2), expectedVector.at(2));


			//test the replaceAll function
			std::string testString2 = "test1, test2, test3";
			std::string from = ", ";
			std::string to = ",";
			std::string expectedString = "test1,test2,test3";
			std::string actualString = replaceAll(testString2, from, to);

			//Test
			Assert::AreEqual(actualString, expectedString);
		}

		// Test for a valid integer string
		TEST_METHOD(TestReadLine)
		{
			// Save the original buffer of std::cin
			std::streambuf* originalCinBuffer = std::cin.rdbuf();
			// Simulate input stream
			std::istringstream input("This is a test\nAnother test\n");

			// Test with ignore = true
    		std::cin.rdbuf(input.rdbuf());
		
    		std::string result = readLine(false);
            Assert::AreEqual(std::string("This is a test"), result);  // Stop execution if this fails

			// Test with ignore = false
            input.str("Another test\n");
			std::cin.rdbuf(input.rdbuf());
		
			result = readLine(true);
			// When ignore is true, it ignores the first character (only if you don't have any cin before)
            Assert::AreEqual(std::string("nother test"), result);  // Stop execution if this fails

			// try using a cin input first then use the readLine function
			input.str("Cin\nNext test");
			std::cin.rdbuf(input.rdbuf());
			std::string cinInput;
			std::cin >> cinInput;

			result = readLine(true);
			Assert::AreEqual(std::string("Next test"), result);  // Stop execution if this fails


			// Restore std::cin
			std::cin.rdbuf(originalCinBuffer);
		}

		// Test for quit function
		TEST_METHOD(TestQuit)
		{
			// Redirect std::cout to write to a string stream
			std::ostringstream output;
			std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
			std::cout.rdbuf(output.rdbuf());

			// Instead of calling quit(), call printGoodbye() so the test doesn't exit the program
			printGoodbye();
            Assert::AreEqual(std::string("Farewell traveler, may our paths cross once more.\n"), output.str());  // Stop execution if this fails

			// Restore std::cout
			std::cout.rdbuf(oldCoutStreamBuf);
		}
		
		// Test the real getCurrentColor function, but only if a console is available
		TEST_METHOD(TestSetAndGetCurrentColor)
		{
			// cerr is used to capture error messages
			std::stringstream error_output;
			std::streambuf* old_cerr = std::cerr.rdbuf(error_output.rdbuf());

			// Test setColor edgecase (color = -1)
			setColor(-1);

			// Check the cerr output for error message
			Assert::IsTrue(error_output.str().find("The color code you have entered is forbidden: ") != string::npos);

			// Restore cerr
			std::cerr.rdbuf(old_cerr);

			setColor(1);

			// Test getCurrentColor
			// Check if it's possible to get the current color
			if (getCurrentColor()!=-1) {
				// Set color to 5 and test
				setColor(5);
				int result = getCurrentColor();
				Assert::AreEqual(5, result);  // Stop execution if this fails
			}
			else {
				// Skip the test if no console is available
				std::cout << "No console/buffer information available, skipping test." << std::endl;
			}
		}

		TEST_METHOD(TestProcessIngredients)
		{
			// Test for valid string ingredients for process_ingred function
			std::string testString = "1*tbsp*test1, 2.5*cup*test2";
			vector<Ingredients> expectedVector = { 
				Ingredients(1, "tbsp", "test1"), 
				Ingredients(2.5, "cup", "test2") };
			vector<Ingredients> actualVector = process_ingred(testString);

			//Test
			Assert::AreEqual(actualVector.at(0).getName(), expectedVector.at(0).getName());
			Assert::AreEqual(actualVector.at(0).getQuantity(), expectedVector.at(0).getQuantity());
			Assert::AreEqual(actualVector.at(0).getUnit(), expectedVector.at(0).getUnit());

			Assert::AreEqual(actualVector.at(1).getName(), expectedVector.at(1).getName());
			Assert::AreEqual(actualVector.at(1).getQuantity(), expectedVector.at(1).getQuantity());
			Assert::AreEqual(actualVector.at(1).getUnit(), expectedVector.at(1).getUnit());


			// Test for malformed input that is internally caught
			std::string mixed_ingred = "\"1*cup*sugar,2*tbsp\"";  // Second ingredient is missing name
			vector<Ingredients> result = process_ingred(mixed_ingred);

			// Check if only the valid ingredient is processed
			Assert::AreEqual(1, (int)result.size());

			// Validate the valid ingredient
			Assert::AreEqual(1.0, result[0].getQuantity());
			Assert::AreEqual(string("cup"), result[0].getUnit());
			Assert::AreEqual(string("sugar"), result[0].getName());


			// Test for empty input (edge case)
			std::string empty_ingred = "";
			vector<Ingredients> result2 = process_ingred(empty_ingred);

			// Check if the result is empty
			Assert::AreEqual(0, (int)result2.size());


			// Capture the error log (std::cerr)
			// Redirect std::cerr to capture the error message
			std::stringstream error_output;
			std::streambuf* old_cerr = std::cerr.rdbuf(error_output.rdbuf());

			std::string invalid_ingred = "\"1*cup\"";  // Missing parts

			// Call the function
			vector<Ingredients> result3 = process_ingred(invalid_ingred);

			// Check if the correct error message was printed to std::cerr
			Assert::IsTrue(error_output.str().find("An unseen force blocks access to the ingredient parts") != string::npos);

			// Restore std::cerr
			std::cerr.rdbuf(old_cerr);

		}

		TEST_METHOD(TestProcessInstructions)
		{
			// Test for valid string with quotes and '||' for process_instructions function
            std::string result = process_instructions("\"Step1||Step2\"");

            // The expected result should have newlines instead of '||' and no quotes
            std::string expected = "Step1\nStep2";
            Assert::AreEqual(expected, result);

			// Test for string without quotes
			result = process_instructions("Step1||Step2");
			expected = "Step1\nStep2";
			Assert::AreEqual(expected, result);

			// Test for string with no '||'
			result = process_instructions("Step1 Step2");
			expected = "Step1 Step2";  // No change expected
			Assert::AreEqual(expected, result);

			// Test for empty string
			result = process_instructions("");
			expected = "";  // No change expected for empty input
			Assert::AreEqual(expected, result);

			// Test for single '||'
			result = process_instructions("||");
			expected = "\n";  // The '||' should be replaced by a newline
			Assert::AreEqual(expected, result);
		}

        TEST_METHOD(TestProcessTime)
        {
			// Test for valid integer string
            Assert::AreEqual(123, process_time("123"));

			// Test for invalid string
			Assert::AreEqual(-1, process_time("abc"));  // Expect -1 for invalid argument

			// Test for out of range value
			Assert::AreEqual(-1, process_time("2147483648"));  // Expect -1 for out of range

			// Test for empty string
			Assert::AreEqual(-1, process_time(""));  // Expect -1 for invalid argument

			// Test for string that represents zero
			Assert::AreEqual(0, process_time("0"));  // Expect 0 for valid input
        }

		// Test for valid difficulty string for process_difficulty function
        TEST_METHOD(TestProcessDifficulty)
        {
            // Test for Easy
            Assert::AreEqual(static_cast<int>(Easy), static_cast<int>(process_difficulty("Easy")));

            // Test for Medium
            Assert::AreEqual(static_cast<int>(Medium), static_cast<int>(process_difficulty("Medium")));

            // Test for Hard
            Assert::AreEqual(static_cast<int>(Hard), static_cast<int>(process_difficulty("Hard")));

            // Test for invalid input
            Assert::AreEqual(static_cast<int>(None), static_cast<int>(process_difficulty("Invalid")));

			// Test for case-insensitive input
			Assert::AreEqual(static_cast<int>(Easy), static_cast<int>(process_difficulty("easy")));
			Assert::AreEqual(static_cast<int>(Medium), static_cast<int>(process_difficulty("medium")));
			Assert::AreEqual(static_cast<int>(Hard), static_cast<int>(process_difficulty("hard")));

			// Test for leading/trailing spaces
			Assert::AreEqual(static_cast<int>(Easy), static_cast<int>(process_difficulty("  Easy  ")));

			// Test for empty string
			Assert::AreEqual(static_cast<int>(None), static_cast<int>(process_difficulty("")));
        }

        TEST_METHOD(TestSetup)
        {
			// Test for an empty file
            RealmOfRecipes app1;
            // Create an empty test file
            ofstream testFile1("empty_recipes.txt");
            testFile1.close();

            // Call the setup function with the empty file
            setup("empty_recipes.txt", app1);

            // Check that no recipes were added
            Assert::AreEqual(size_t(0), app1.allRecipes.size());  // Should have 0 recipes
            Assert::AreEqual(size_t(0), app1.allSeries.size());   // Should have 0 series

            // Clean up test file
            remove("empty_recipes.txt");


			// Test for a file with only the header
			RealmOfRecipes app2;
			// Create a test file with only a header
			ofstream testFile2("header_only.txt");
			testFile2 << "Name\tSeries\tDescription\tIngredients\tInstructions\tTime\tDifficulty\n"; // Header
			testFile2.close();

			// Call the setup function with the header-only file
			setup("header_only.txt", app2);

			// Check that no recipes were added
			Assert::AreEqual(size_t(0), app2.allRecipes.size());  // Should have 0 recipes
			Assert::AreEqual(size_t(0), app2.allSeries.size());   // Should have 0 series

			// Clean up test file
			remove("header_only.txt");


			// Test for a file with known data
			RealmOfRecipes app;
			// Create a test file with known data
			ofstream testFile("test_recipes.txt");
			testFile << "Name\tSeries\tDescription\tIngredients\tInstructions\tTime\tDifficulty\n"; // Header
			testFile << "Pancakes\tBreakfast\tFluffy pancakes recipe\t1 cup flour*cup*flour, 1 egg*egg*egg\tMix ingredients\t15\tEasy\n";
			testFile << "Spaghetti\tDinner\tClassic spaghetti recipe\t200g spaghetti*gram*spaghetti, 1 tomato*tomato*tomato\tCook spaghetti\t30\tMedium\n";
			testFile.close();

			// Call the setup function with the test file
			setup("test_recipes.txt", app);

			// Check that the recipes were added correctly
			Assert::AreEqual(size_t(2), app.allRecipes.size());  // Should have 2 recipes

			// Check the first recipe
			Assert::AreEqual(string("Pancakes"), app.allRecipes[0].getName());
			Assert::AreEqual(string("Breakfast"), app.allRecipes[0].getSeries());
			Assert::AreEqual(string("Fluffy pancakes recipe"), app.allRecipes[0].getDescription());
			Assert::AreEqual(15, app.allRecipes[0].getTime());
			Assert::AreEqual(static_cast<int>(Easy), static_cast<int>(app.allRecipes[0].getDifficulty()));

			// Check the second recipe
			Assert::AreEqual(string("Spaghetti"), app.allRecipes[1].getName());
			Assert::AreEqual(string("Dinner"), app.allRecipes[1].getSeries());
			Assert::AreEqual(string("Classic spaghetti recipe"), app.allRecipes[1].getDescription());
			Assert::AreEqual(30, app.allRecipes[1].getTime());
			Assert::AreEqual(static_cast<int>(Medium), static_cast<int>(app.allRecipes[1].getDifficulty()));

			// Check that allSeries is updated
			Assert::AreEqual(size_t(2), app.allSeries.size());
			Assert::IsTrue(find(app.allSeries.begin(), app.allSeries.end(), "Breakfast") != app.allSeries.end());
			Assert::IsTrue(find(app.allSeries.begin(), app.allSeries.end(), "Dinner") != app.allSeries.end());

			// Clean up test file
			remove("test_recipes.txt");

        }

		TEST_METHOD(TestDisplayRecipes)
		{
			// Redirect cout to a string stream to capture the output
			std::ostringstream buffer;
			std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

			// sample ingredients
			vector<Ingredients> ingredients = {
				Ingredients(1, "cup", "Pasta"),
				Ingredients(1, "can", "Tomato Sauce")
			};
			vector<Ingredients> ingredients2 = {
				Ingredients(1, "null", "Lettuce"),
				Ingredients(1, "null", "Tomato"),
				Ingredients(1, "null", "Vinaigrette")
			};

			// Sample recipes
			vector<Recipes> recipes = {
				Recipes("Pasta", "Italian", "Delicious spaghetti with tomato sauce", ingredients, "Boil and mix", 20, Easy),
				Recipes("Salad", "Vegetarian", "Fresh garden salad with vinaigrette", ingredients2, "Mix all ingredients", 15, Medium)
			};

			// Short display case
			display(recipes, true);
			// Check the output for short display
			Assert::AreEqual("Pasta (Italian) - \033[92m20 minutes\033[0m - \033[92mEasy\033[0m\n"
				"Salad (Vegetarian) - \033[92m15 minutes\033[0m - \033[33mMedium\033[0m\n", buffer.str().c_str());

			// Clear the buffer for the next case
			buffer.str("");
			buffer.clear();

			// Long display case
			display(recipes, false);
			// Check the output for long display
			Assert::AreEqual("Name: Pasta\n"
				"Series: Italian\n"
				"Time: \033[92m20 minutes\033[0m\n"
				"Difficulty: \033[92mEasy\033[0m\n"
				"Description: Delicious spaghetti with tomato sauce\n"
				"Ingredients: \n"
				"- 1 cup Pasta\n"
				"- 1 can Tomato Sauce\n"
				"Instructions: \nBoil and mix\n"
				"\n"
				"Name: Salad\n"
				"Series: Vegetarian\n"
				"Time: \033[92m15 minutes\033[0m\n"
				"Difficulty: \033[33mMedium\033[0m\n"
				"Description: Fresh garden salad with vinaigrette\n"
				"Ingredients: \n"
				"- 1 Lettuce\n"
				"- 1 Tomato\n"
				"- 1 Vinaigrette\n"
				"Instructions: \nMix all ingredients\n\n", buffer.str().c_str());


			// Restore original cout buffer
			std::cout.rdbuf(oldCoutBuffer);
		}

		TEST_METHOD(TestSortByDifficulty)
		{
			// Sample recipes
			vector<Recipes> recipes = {
				Recipes("Pasta", "Italian", "Delicious spaghetti with tomato sauce", {}, "Boil and mix", 20, Easy),
				Recipes("Salad", "Vegetarian", "Fresh garden salad with vinaigrette", {}, "Mix all ingredients", 15, Medium),
				Recipes("Pizza", "Italian", "Cheesy pizza with tomato sauce", {}, "Bake and serve", 30, Hard)
			};

			// check pairwise comparison
			Assert::IsTrue(sortByDifficulty(recipes[0], recipes[1]));  // Easy < Medium
			Assert::IsTrue(sortByDifficulty(recipes[1], recipes[2]));  // Medium < Hard
			Assert::IsTrue(sortByDifficulty(recipes[0], recipes[2]));  // Easy < Hard

			// check for reverse comparison
			Assert::IsFalse(sortByDifficulty(recipes[1], recipes[0]));  // Medium > Easy
			Assert::IsFalse(sortByDifficulty(recipes[2], recipes[1]));  // Hard > Medium
			Assert::IsFalse(sortByDifficulty(recipes[2], recipes[0]));  // Hard > Easy

			// check for equal difficulty
			Assert::IsFalse(sortByDifficulty(recipes[0], recipes[0]));  // Equal difficulty
		}

		TEST_METHOD(TestSortByTime)
		{
			// Sample recipes
			vector<Recipes> recipes = {
				Recipes("Pasta", "Italian", "Delicious spaghetti with tomato sauce", {}, "Boil and mix", 20, Easy),
				Recipes("Salad", "Vegetarian", "Fresh garden salad with vinaigrette", {}, "Mix all ingredients", 15, Medium),
				Recipes("Pizza", "Italian", "Cheesy pizza with tomato sauce", {}, "Bake and serve", 30, Hard)
			};

			// check pairwise comparison
			Assert::IsTrue(sortByTime(recipes[1], recipes[0]));  // Salad < Pasta
			Assert::IsTrue(sortByTime(recipes[0], recipes[2]));  // Pasta < Pizza
			Assert::IsTrue(sortByTime(recipes[1], recipes[2]));  // Salad < Pizza

			// check for reverse comparison
			Assert::IsFalse(sortByTime(recipes[0], recipes[1]));  // Pasta > Salad
			Assert::IsFalse(sortByTime(recipes[2], recipes[0]));  // Pizza > Pasta
			Assert::IsFalse(sortByTime(recipes[2], recipes[1]));  // Pizza > Salad

			// check for equal time
			Assert::IsFalse(sortByTime(recipes[0], recipes[0]));  // Equal time
		}


		TEST_METHOD(TestApplySettingFilters) 
		{
			// Redirect cout to a string stream to capture the output
			std::ostringstream buffer;
			std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

			// Sample recipes
			vector<Recipes> recipes = {
				Recipes("Pasta", "Italian", "Delicious spaghetti with tomato sauce", {}, "Boil and mix", 20, Easy),
				Recipes("Salad", "Vegetarian", "Fresh garden salad with vinaigrette", {}, "Mix all ingredients", 15, Medium),
				Recipes("Soup", "Vegetarian", "Warm soup with vegetables", {}, "Boil and simmer", 45, Medium),
				Recipes("Pizza", "Italian", "Cheesy pizza with tomato sauce", {}, "Bake and serve", 30, Hard),
				Recipes("Lasagna", "Italian", "Layered pasta with cheese and tomato sauce", {}, "Bake and serve", 90, Hard)
			};

			// Case 1: Filter by time (less than 30 minutes) and no difficulty filter
			vector<Recipes> result = applySetting(recipes, 1, 0);
			Assert::AreEqual(2, (int)result.size());
			Assert::AreEqual("Pasta (Italian) - \033[92m20 minutes\033[0m - \033[92mEasy\033[0m", result[0].toStringShort().c_str());
			Assert::AreEqual("Salad (Vegetarian) - \033[92m15 minutes\033[0m - \033[33mMedium\033[0m", result[1].toStringShort().c_str());

			buffer.str(""); buffer.clear();  // Clear the buffer for next test

			// Case 2: Filter by time (30-60 minutes) and difficulty = Medium
			result = applySetting(recipes, 2, 2);
			Assert::AreEqual(1, (int)result.size());
			Assert::AreEqual("Soup (Vegetarian) - \033[33m45 minutes\033[0m - \033[33mMedium\033[0m", result[0].toStringShort().c_str());

			buffer.str(""); buffer.clear();  // Clear the buffer for next test

			// Case 3: Filter by time (greater than 60 minutes) and difficulty = Hard
			result = applySetting(recipes, 3, 3);
			Assert::AreEqual(1, (int)result.size());

			Assert::AreEqual("Lasagna (Italian) - \033[91m90 minutes\033[0m - \033[91mHard\033[0m", result[0].toStringShort().c_str());

			buffer.str(""); buffer.clear();  // Clear the buffer for next test

			// Case 4: Filter with no matching results (timeFilter = 1, difficulty = Hard)
			result = applySetting(recipes, 1, 3);
			Assert::AreEqual(0, (int)result.size());

			buffer.str(""); buffer.clear();  // Clear the buffer for next test

			// Case 5: Filter with no recipes (empty input)
			result = applySetting({}, 1, 0);
			Assert::AreEqual(0, (int)result.size());

			buffer.str(""); buffer.clear();  // Clear the buffer for next test

			// Case 6: Filter with just difficulty filter (difficulty = Easy)
			result = applySetting(recipes, 0, 1);
			Assert::AreEqual(1, (int)result.size());
			Assert::AreEqual("Pasta (Italian) - \033[92m20 minutes\033[0m - \033[92mEasy\033[0m", result[0].toStringShort().c_str());

			buffer.str(""); buffer.clear();  // Clear the buffer for next test

			// Restore original cout buffer
			std::cout.rdbuf(oldCoutBuffer);
		}

		TEST_METHOD(TestPrintSettings) 
		{
			// Redirect cout to a string stream to capture the output
			std::ostringstream buffer;
			std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

			// Case 1: All filters set (timeFilter = 2, difficultyFilter = 1, sortFilter = 3)
			printSettings(2, 1, 3);
			Assert::AreEqual("\nActive selections: \nDifficulty: Easy \nTime: 30 to 60 minutes \nActive arrangement: \nSort by time \n\n", buffer.str().c_str());

			// Clear buffer for next case
			buffer.str(""); buffer.clear();

			// Case 2: No filters set (timeFilter = 0, difficultyFilter = 0, sortFilter = 0)
			printSettings(0, 0, 0);
			Assert::AreEqual("\nActive selections: \nNaught \nActive arrangement: \nNaught \n\n", buffer.str().c_str());

			// Clear buffer for next case
			buffer.str(""); buffer.clear();

			// Case 3: Only time filter set (timeFilter = 3, difficultyFilter = 0, sortFilter = 0)
			printSettings(3, 0, 0);
			Assert::AreEqual("\nActive selections: \nTime: More than 60 minutes \nActive arrangement: \nNaught \n\n", buffer.str().c_str());

			// Clear buffer for next case
			buffer.str(""); buffer.clear();

			// Case 4: Only difficulty and sorting set (timeFilter = 0, difficultyFilter = 2, sortFilter = 1)
			printSettings(0, 2, 1);
			Assert::AreEqual("\nActive selections: \nDifficulty: Medium \nActive arrangement: \nSort by difficulty \n\n", buffer.str().c_str());

			// Clear buffer for next case
			buffer.str(""); buffer.clear();

			// Case 5: Sorting only (timeFilter = 0, difficultyFilter = 0, sortFilter = 4)
			printSettings(0, 0, 4);
			Assert::AreEqual("\nActive selections: \nNaught \nActive arrangement: \nSort by time reverse \n\n", buffer.str().c_str());

			// Restore original cout buffer
			std::cout.rdbuf(oldCoutBuffer);
		}

		TEST_METHOD(TestHandleDifficultyFilter) 
		{
			RealmOfRecipes app;
			app.difficultyFilter = 0;

			// Save the original buffer of std::cin
			std::streambuf* originalCinBuffer = std::cin.rdbuf();

			// Simulate user input 2 for medium difficulty, 4 to exit loop
			istringstream input("2\n4\n");
			cin.rdbuf(input.rdbuf());  // Mock user input

			handleDifficultyFilter(app);
			Assert::AreEqual(2, app.difficultyFilter);  // Check if the filter was applied correctly


			// Case for back input
			istringstream input2("4\n");
			cin.rdbuf(input2.rdbuf());  // Mock user input

			handleDifficultyFilter(app);
			Assert::AreEqual(2, app.difficultyFilter);  // Check if the filter was not applied for invalid input


			// Case for invalid input
			app.difficultyFilter = 0;

			istringstream input3("abc\n4\n");
			cin.rdbuf(input3.rdbuf());  // Mock user input

			handleDifficultyFilter(app);
			Assert::AreEqual(0, app.difficultyFilter);  // Check if the filter was not applied for invalid input
		
			// Restore std::cin
			std::cin.rdbuf(originalCinBuffer);
		}

		TEST_METHOD(TestHandleTimeFilter) 
		{
			RealmOfRecipes app;
			app.timeFilter = 0;

			// Save the original buffer of std::cin
			std::streambuf* originalCinBuffer = std::cin.rdbuf();

			// Simulate user input 3 for more than 60 minutes, 4 to exit loop
			istringstream input("3\n4\n");
			cin.rdbuf(input.rdbuf());  // Mock user input

			handleTimeFilter(app);
			Assert::AreEqual(3, app.timeFilter);  // Check if the filter was applied correctly


			// Case for back input

			// Simulate user input
			istringstream input2("4\n");
			cin.rdbuf(input2.rdbuf());  // Mock user input

			handleTimeFilter(app);
			Assert::AreEqual(3, app.timeFilter);  // Check if the filter was not applied for invalid input


			// Case for invalid input
			app.timeFilter = 0;

			// Simulate user input
			istringstream input3("abc\n4\n");
			cin.rdbuf(input3.rdbuf());  // Mock user input

			handleTimeFilter(app);
			Assert::AreEqual(0, app.timeFilter);  // Check if the filter was not applied for invalid input

			// Restore std::cin
			std::cin.rdbuf(originalCinBuffer);
		}

		TEST_METHOD(TestHandleSort) 
		{
			RealmOfRecipes app;
			app.sortFilter = 0;
			app.allRecipes = {
				Recipes("Pasta", "Italian", "Delicious spaghetti with tomato sauce", {}, "Boil and mix", 20, Easy),
				Recipes("Salad", "Vegetarian", "Fresh garden salad with vinaigrette", {}, "Mix all ingredients", 15, Medium),
				Recipes("Pizza", "Italian", "Cheesy pizza with tomato sauce", {}, "Bake and serve", 30, Hard)
			};

			// Save the original buffer of std::cin
			std::streambuf* originalCinBuffer = std::cin.rdbuf();

			// Simulate user input for Sort by difficulty and back (5)
			istringstream input("1\n5\n");
			cin.rdbuf(input.rdbuf());  // Mock user input

			handleSort(app);
			Assert::AreEqual(1, app.sortFilter);  // Check if the filter was applied correctly
			// Check if the correct sort filter was applied
			Assert::AreEqual(std::string("Pasta"), app.allRecipes[0].getName());
			Assert::AreEqual(std::string("Salad"), app.allRecipes[1].getName());
			Assert::AreEqual(std::string("Pizza"), app.allRecipes[2].getName());

			// Simulate user input for Sort by difficulty reverse and back
			istringstream input2("2\n5\n");
			cin.rdbuf(input2.rdbuf());  // Mock user input

			handleSort(app);
			Assert::AreEqual(2, app.sortFilter);  // Check if the filter was applied correctly
			// Check if the correct sort filter was applied
			Assert::AreEqual(std::string("Pizza"), app.allRecipes[0].getName());
			Assert::AreEqual(std::string("Salad"), app.allRecipes[1].getName());
			Assert::AreEqual(std::string("Pasta"), app.allRecipes[2].getName());

			// Simulate user input for Sort by time
			istringstream input3("3\n5\n");
			cin.rdbuf(input3.rdbuf());  // Mock user input

			handleSort(app);
			Assert::AreEqual(3, app.sortFilter);  // Check if the filter was applied correctly
			// Check if the correct sort filter was applied
			Assert::AreEqual(std::string("Salad"), app.allRecipes[0].getName());
			Assert::AreEqual(std::string("Pasta"), app.allRecipes[1].getName());
			Assert::AreEqual(std::string("Pizza"), app.allRecipes[2].getName());

			// Simulate user input for Sort by time reverse
			istringstream input4("4\n5\n");
			cin.rdbuf(input4.rdbuf());  // Mock user input

			handleSort(app);
			Assert::AreEqual(4, app.sortFilter);  // Check if the filter was applied correctly
			// Check if the correct sort filter was applied
			Assert::AreEqual(std::string("Pizza"), app.allRecipes[0].getName());
			Assert::AreEqual(std::string("Pasta"), app.allRecipes[1].getName());
			Assert::AreEqual(std::string("Salad"), app.allRecipes[2].getName());

			// Case for back input

			// Simulate user input
			istringstream input5("5\n");
			cin.rdbuf(input5.rdbuf());  // Mock user input

			handleSort(app);
			Assert::AreEqual(4, app.sortFilter);  // Check if the filter was not applied for invalid input

			// Case for invalid input
			app.sortFilter = 0;

			// Simulate user input
			istringstream input6("abc\n5\n");
			cin.rdbuf(input6.rdbuf());  // Mock user input

			handleSort(app);
			Assert::AreEqual(0, app.sortFilter);  // Check if the filter was not applied for invalid input

			// Restore std::cin
			std::cin.rdbuf(originalCinBuffer);
		}

		TEST_METHOD(TestShowInvalidChoiceMessage)
		{
			// Redirect cout to a string stream to capture the output
			std::ostringstream buffer;
			std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

			// Redirect cin to simulate user input (you can provide any input here)
			std::istringstream input("invalid input");
			std::streambuf* oldCinBuffer = std::cin.rdbuf(input.rdbuf());


			showInvalidChoiceMessage();
			Assert::AreEqual("An unwise choice has been made. Seek another path.\n", buffer.str().c_str());

			// Restore original cout and cin buffers
			std::cout.rdbuf(oldCoutBuffer);
			std::cin.rdbuf(oldCinBuffer);
		}

		TEST_METHOD(TestSetSettings)
		{
			RealmOfRecipes app;
			app.timeFilter = 2;
			app.difficultyFilter = 3;
			app.sortFilter = 1;

			// Save the original buffer of std::cin
			std::streambuf* originalCinBuffer = std::cin.rdbuf();

			// Simulate user input for reset filters
			// 3 -> Reset filters, 6 -> Exit loop, 2 -> Save settings
			istringstream input("3\n6\n2\n");
			cin.rdbuf(input.rdbuf());  // Mock user input

			setSettings(app);
			// Check if the filters have been reset 
			Assert::AreEqual(0, app.timeFilter);
			Assert::AreEqual(0, app.difficultyFilter);


			// Simulate user input for reset sort
			// 5 -> Reset sort, 6 -> Exit loop, 2 -> Save settings
			istringstream input2("5\n6\n2\n");
			cin.rdbuf(input2.rdbuf());  // Mock user input

			setSettings(app);
			Assert::AreEqual(0, app.sortFilter);  // Check if the sort filter was reset

			//THE OTHER OPTIONS FOR THIS JUST LEADS TO CALLING OTHER FUNCTIONS THAT ARE TESTED IN SEPARATE TESTS


			// Restore std::cin
			std::cin.rdbuf(originalCinBuffer);
		}

		TEST_METHOD(TestRandomRecipe)
		{
			vector<Recipes> allRecipes = {
				Recipes("Pasta", "Italian", "Delicious spaghetti with tomato sauce", {}, "Boil and mix", 20, Easy),
				Recipes("Salad", "Vegetarian", "Fresh garden salad with vinaigrette", {}, "Mix all ingredients", 15, Medium),
				Recipes("Pizza", "Italian", "Cheesy pizza with tomato sauce", {}, "Bake and serve", 30, Hard)
			};

			int timeFilter = 0;
			int difficultyFilter = 0;
			int sortFilter = 0;

			// redirect cout to a string stream to capture the output
			std::ostringstream buffer;
			std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

			srand(42); // Control randomness
			random(allRecipes, timeFilter, difficultyFilter, sortFilter);

			// Check if the output has Salad in it
			Assert::IsTrue(buffer.str().find("Salad") != string::npos);

			// clear the buffer for the next test
			buffer.str(""); buffer.clear();


			// Empty recipes case
			vector<Recipes> emptyRecipes = {};
			random(emptyRecipes, timeFilter, difficultyFilter, sortFilter);

			// Check if the output is No matching recipes found
			Assert::AreEqual("No recipes align with your search.\n", buffer.str().c_str());

			// clear the buffer for the next test
			buffer.str(""); buffer.clear();
			
			// Empty applied filters case
			random(allRecipes, 3, 1, 0);

			// Check if the output is No matching recipes found
			Assert::AreEqual("\nNo such recipe exists within the forgotten archives.\n\n", buffer.str().c_str());

			// Restore original cout buffer
			std::cout.rdbuf(oldCoutBuffer);
		}


		/** Testing Search by name function 
		* 
		*/
		TEST_METHOD(TestSearchByName)
		{
			std::vector<Recipes> allRecipes;

			//Mock user input
			std::istringstream input("apple\n");
			std::cin.rdbuf(input.rdbuf());

			std::vector<Recipes> results = searchByName(allRecipes);		
			Assert::IsTrue(results.empty());

			
			Recipes recipe1("Apple Pie", "", "", {}, "", 0, Easy);
			Recipes recipe2("Banana Bread", "", "", {}, "", 0, Easy);
			allRecipes = { recipe1, recipe2 };

			//Mock user input
			std::istringstream input2("apple\n");
			std::cin.rdbuf(input2.rdbuf());

			results = searchByName(allRecipes);

			Assert::AreEqual(size_t(1), results.size());
			Assert::AreEqual(std::string("Apple Pie"), results[0].getName());
			

			Recipes recipe3("Apple Crumble", "", "", {}, "", 0, Easy);
			allRecipes = { recipe1, recipe2, recipe3 };

			// Mock user input
			std::istringstream input3("apple\n");
			std::cin.rdbuf(input3.rdbuf());

			results = searchByName(allRecipes);

			Assert::AreEqual(size_t(2), results.size());
			Assert::AreEqual(std::string("Apple Pie"), results[0].getName());
			Assert::AreEqual(std::string("Apple Crumble"), results[1].getName());
			
			//test no results
			// Mock user input
			std::istringstream input4("orange\n");
			std::cin.rdbuf(input4.rdbuf());

			results = searchByName(allRecipes);

			Assert::IsTrue(results.empty());		
		}

		/** Testing Search by ingredients function
		* @see Support.cpp
		* @test
		*/
		TEST_METHOD(TestSearchByIngredients)
		{
			std::vector<Recipes> allRecipes;

			//Mock user input
			std::istringstream input("apple\n");
			std::cin.rdbuf(input.rdbuf());

			std::vector<Recipes> results = searchByIngredient(allRecipes, 0, 0, 0);
			Assert::IsTrue(results.empty());

			//// Test for a single ingredient (banana)
			//Recipes recipe1 = Recipes("Apple Pie", "", "", { Ingredients(1, "", "apple") }, "", 0, Easy);
			//Recipes recipe2 = Recipes("Banana Bread", "", "", { Ingredients(1, "", "banana") }, "", 0, Easy);
			//allRecipes = { recipe1, recipe2 };

			//// Mock user input for "banana"
			//std::istringstream input2("banana"); 
			//std::cin.rdbuf(input2.rdbuf());
			////print input
			//std::cout << input2.str() << std::endl;

			//results = searchByIngredient(allRecipes, 0, 0, 0);

			////print allRecipes
			//for (auto& recipe : allRecipes) {
			//	std::cout << recipe.getName() << std::endl;
			//}

			////print result
			//for (auto& recipe : results) {
			//	std::cout << recipe.getName() << std::endl;
			//}

			//// Check if the function finds exactly one recipe, and it's the correct one
			//Assert::AreEqual(size_t(1), results.size());
			//Assert::AreEqual(std::string("Banana Bread"), results[0].getName());

			////Test for multiple results
			//Recipes recipe3 = Recipes("Apple Crumble", "", "", { Ingredients(1, "apple", "apple"), Ingredients(1, "sugar", "cup") }, "", 0, Easy);
			//Recipes recipe4 = Recipes("Lemon Juice", "", "", { Ingredients(1, "lemon", "lemon"), Ingredients(1, "sugar", "cup") }, "", 0, Easy);
			//allRecipes = { recipe1, recipe2, recipe3, recipe4 };

			////Mock user input
			//std::istringstream input3("sugar\n");
			//std::cin.rdbuf(input3.rdbuf());

			//results = searchByIngredient(allRecipes, 0, 0, 0);

			//Assert::AreEqual(size_t(2), results.size());
			//Assert::AreEqual(std::string("Apple Crumble"), results[0].getName());
			//Assert::AreEqual(std::string("Lemon Juice"), results[1].getName());

			////Test for multiple ingredients
			//
			////Mock user input
			//std::istringstream input4("apple\nsugar\n");
			//std::cin.rdbuf(input4.rdbuf());

			//results = searchByIngredient(allRecipes, 0, 0, 0);

			//Assert::AreEqual(size_t(1), results.size());
			//Assert::AreEqual(std::string("Apple Crumble"), results[0].getName());





		}

	};
}