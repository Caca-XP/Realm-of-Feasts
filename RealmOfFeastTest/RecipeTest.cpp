#include "pch.h"
#include "CppUnitTest.h"
#include "../Recipes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RealmOfFeastTest
{
	TEST_CLASS(RecipeTest)
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
			vector<Ingredients> testIngredients = { Ingredients(10, "testUnit", "testIng") };
			Level testLevel = Level(3);
			std::string expectedName = "testName";
			std::string expectedSeries = "testSeries";
			std::string expectedDescription = "testDescription";
			std::string expectedInstructions = "testInstructions";
			int expectedTime = 10;
			int expectedLevel = 3;
			Recipes testRecipe = Recipes("testName", "testSeries", "testDescription", testIngredients, "testInstructions", 10, testLevel);
			int actualLevel = testRecipe.getDifficulty();
			vector<std::string> expectedIngNames = { "testIng" };


			//Test
			Assert::AreEqual(testRecipe.getName(), expectedName);
			Assert::AreEqual(testRecipe.getSeries(), expectedSeries);
			Assert::AreEqual(testRecipe.getDescription(), expectedDescription);
			Assert::AreEqual(testRecipe.getIngredients().at(0).getName(), testIngredients.at(0).getName());
			Assert::AreEqual(testRecipe.getInstructions(), expectedInstructions);
			Assert::AreEqual(testRecipe.getTime(), expectedTime);
			Assert::AreEqual(actualLevel, expectedLevel);
			Assert::AreEqual(testRecipe.getIngredientsNames().at(0), expectedIngNames.at(0));

			//change the expected name and description
			expectedName = "testName2";
			expectedDescription = "testDescription2";

			//test if the name and description are not equal to the expected values
			Assert::AreNotEqual(testRecipe.getName(), expectedName);
			Assert::AreNotEqual(testRecipe.getDescription(), expectedDescription);
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


	};
}