#include "pch.h"
#include "CppUnitTest.h"
#include "../../App.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RealmOfFeastTest
{
	TEST_CLASS(RealmOfFeastTest)
	{
	public:
		
		/**
		 * Test for the default constructor of the Recipes class
		 * @see Recipes.cpp
		 * @test
		 */
		TEST_METHOD(TestRecipesDefaultConstructor)
		{
			Recipes testRecipe = Recipes();
			std::string expectedName = "";
			std::string expectedSeries = "";
			std::string expectedDescription = "";
			std::string expectedInstructions = "";
			int expectedTime = 0;
			int expectedLevel = 0;
			int actualLevel = testRecipe.getDifficulty();

			//Test
			Assert::AreEqual(testRecipe.getName(), expectedName);
			Assert::AreEqual(testRecipe.getSeries(), expectedSeries);
			Assert::AreEqual(testRecipe.getDescription(), expectedDescription);
			Assert::AreEqual(testRecipe.getInstructions(), expectedInstructions);
			Assert::AreEqual(testRecipe.getTime(), expectedTime);
			Assert::AreEqual(actualLevel, expectedLevel);
		}

		/**
		 * Test for the parameterized constructor of the Recipes class
		 * @see Recipes.cpp
		 * @test
		 */
		TEST_METHOD(TestRecipesParameterizedConstructor)
		{
			vector<Ingredients> testIngredients = { Ingredients(10, "testUnit", "testIng")};
			Level testLevel = Level(3);
			std::string expectedName = "testName";
			std::string expectedSeries = "testSeries";
			std::string expectedDescription = "testDescription";
			std::string expectedInstructions = "testInstructions";
			int expectedTime = 10;
			int expectedLevel = 3;
			Recipes testRecipe = Recipes("testName", "testSeries", "testDescription", testIngredients, "testInstructions", 10, testLevel);
			int actualLevel = testRecipe.getDifficulty();


			//Test
			Assert::AreEqual(testRecipe.getName(), expectedName);
			Assert::AreEqual(testRecipe.getSeries(), expectedSeries);
			Assert::AreEqual(testRecipe.getDescription(), expectedDescription);
			Assert::AreEqual(testRecipe.getIngredients().at(0).getName(), testIngredients.at(0).getName());
			Assert::AreEqual(testRecipe.getInstructions(), expectedInstructions);
			Assert::AreEqual(testRecipe.getTime(), expectedTime);
			Assert::AreEqual(actualLevel, expectedLevel);

			//change the expected name and description
			expectedName = "testName2";
			expectedDescription = "testDescription2";

			//test if the name and description are not equal to the expected values
			Assert::AreNotEqual(testRecipe.getName(), expectedName);
			Assert::AreNotEqual(testRecipe.getDescription(), expectedDescription);
		}

		/**
		 * Test for the default constructor of the Ingredients class
		 * @see Ingredients.cpp
		 * @test
		 */
		TEST_METHOD(TestIngredientsDefaultConstructor)
		{
			Ingredients testIngredient = Ingredients();
			std::string expectedName = "";
			std::string expectedUnit = "";
			double expectedQuantity = 0;

			//Test
			Assert::AreEqual(testIngredient.getName(), expectedName);
			Assert::AreEqual(testIngredient.getUnit(), expectedUnit);
			Assert::AreEqual(testIngredient.getQuantity(), expectedQuantity);
		}

		/**
		 * Test for the parameterized constructor of the Ingredients class
		 * @see Ingredients.cpp
		 * @test
		 */
		TEST_METHOD(TestIngredientsParameterizedConstructor)
		{
			std::string expectedName = "testName";
			std::string expectedUnit = "testUnit";
			double expectedQuantity = 10;
			Ingredients testIngredient = Ingredients(10, "testUnit", "testName");

			//Test
			Assert::AreEqual(testIngredient.getName(), expectedName);
			Assert::AreEqual(testIngredient.getUnit(), expectedUnit);
			Assert::AreEqual(testIngredient.getQuantity(), expectedQuantity);

			//change the expected name and quantity
			expectedName = "testName2";
			expectedQuantity = 20;

			//test if the name and quantity are not equal to the expected values
			Assert::AreNotEqual(testIngredient.getName(), expectedName);
			Assert::AreNotEqual(testIngredient.getQuantity(), expectedQuantity);
		}

		/**
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
			vector<string> actualVector = split_string(testString, delimiter);

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

		/**
		 * Test the enum Level
		 * @see Recipes.cpp
		 * @test
		 */
		TEST_METHOD(TestLevel)
		{
			enum Level testLevel = Hard;
			int expectedLevel = 3;
			int actualLevel = testLevel;

			//Test
			Assert::AreEqual(actualLevel, expectedLevel);

			//change the actual level
			actualLevel = Easy;			

			//test if the level is not equal to the expected value
			Assert::AreNotEqual(actualLevel, expectedLevel);
			Assert::AreEqual(actualLevel, 1);
		}

		/**
		 * Test process ingredients function of the App
		 * @see App.cpp
		 * @test
		 */
		TEST_METHOD(TestProcessIngredients)
		{
			//test the processIngredients function
			std::string testIngredient = "1*unit1*ingredient1, 2*unit2*ingredient2, 3*unit3*ingredient3, 4*unit4*ingredient4, 5*unit5*ingredient5";
			vector<Ingredients> expectedIngredients = { Ingredients(1, "unit1", "ingredient1"), Ingredients(2, "unit2", "ingredient2"), Ingredients(3, "unit3", "ingredient3"), Ingredients(4, "unit4", "ingredient4"), Ingredients(5, "unit5", "ingredient5") };
			vector<Ingredients> actualIngredients;

			// Check if process_ingred throws any exceptions
			try {
				actualIngredients = process_ingred(testIngredient);
			}
			catch (const std::exception& ex) {
				Assert::Fail(L"Exception thrown during process_ingred execution.");
			}
			
			//Test names of the ingredients match
			Assert::AreEqual(actualIngredients.at(0).getName(), expectedIngredients.at(0).getName());
			Assert::AreEqual(actualIngredients.at(1).getName(), expectedIngredients.at(1).getName());
			Assert::AreEqual(actualIngredients.at(2).getName(), expectedIngredients.at(2).getName());
			Assert::AreEqual(actualIngredients.at(3).getName(), expectedIngredients.at(3).getName());
			Assert::AreEqual(actualIngredients.at(4).getName(), expectedIngredients.at(4).getName());

			//Test units of the ingredients match
			Assert::AreEqual(actualIngredients.at(0).getUnit(), expectedIngredients.at(0).getUnit());
			Assert::AreEqual(actualIngredients.at(1).getUnit(), expectedIngredients.at(1).getUnit());
			Assert::AreEqual(actualIngredients.at(2).getUnit(), expectedIngredients.at(2).getUnit());
			Assert::AreEqual(actualIngredients.at(3).getUnit(), expectedIngredients.at(3).getUnit());
			Assert::AreEqual(actualIngredients.at(4).getUnit(), expectedIngredients.at(4).getUnit());

			//Test quantities of the ingredients match
			Assert::AreEqual(actualIngredients.at(0).getQuantity(), expectedIngredients.at(0).getQuantity());
			Assert::AreEqual(actualIngredients.at(1).getQuantity(), expectedIngredients.at(1).getQuantity());
			Assert::AreEqual(actualIngredients.at(2).getQuantity(), expectedIngredients.at(2).getQuantity());
			Assert::AreEqual(actualIngredients.at(3).getQuantity(), expectedIngredients.at(3).getQuantity());
			Assert::AreEqual(actualIngredients.at(4).getQuantity(), expectedIngredients.at(4).getQuantity());
			

		}
	};
}
