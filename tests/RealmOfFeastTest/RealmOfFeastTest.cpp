#include "pch.h"
#include "CppUnitTest.h"
#include "../../App.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RealmOfFeastTest
{
	TEST_CLASS(RealmOfFeastTest)
	{
	public:
		
		/*TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(1, 1);
		}*/

		//Test for the default constructor of the Recipes class
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

		//Test for the parameterized constructor of the Recipes class
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

		//Test for the default constructor of the Ingredients class
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

		//Test for the parameterized constructor of the Ingredients class
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

		//test the support functions
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
	};
}
