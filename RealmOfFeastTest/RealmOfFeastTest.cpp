#include "pch.h"
#include "CppUnitTest.h"
#include "../RealmOfRecipes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace RealmOfFeastTest
{
	TEST_CLASS(TestRealmOfRecipesClass)
	{
		public:

			/** Testing the default constructor of the RealmOfRecipes class
			 * @see RealmOfRecipes.cpp
			 * @test

			*/
			TEST_METHOD(TestDefaultConstructor)
			{
				RealmOfRecipes testRealm = RealmOfRecipes();
				vector<Recipes> expectedRecipes = {};
				int expectedTime = 0;
				int expectedDifficulty = 0;
				int expectedSort = 0;
				vector<string> expectedSeries = {};

				//Test
				Assert::AreEqual(testRealm.allRecipes.size(), expectedRecipes.size());
				Assert::AreEqual(testRealm.timeFilter, expectedTime);
				Assert::AreEqual(testRealm.difficultyFilter, expectedDifficulty);
				Assert::AreEqual(testRealm.sortFilter, expectedSort);
				Assert::AreEqual(testRealm.allSeries.size(), expectedSeries.size());

			}

			/** Testing the parameterized constructor of the RealmOfRecipes class
			 * @see RealmOfRecipes.cpp
			 * @test
			 */
			TEST_METHOD(TestParameterizedConstructor)
            {
				vector<Ingredients> testIngredients = { Ingredients(10, "testUnit", "testIngred") };
				Level testLevel = Level(3);
				vector<Recipes> testRecipes = { Recipes("testName", "testSeries", "testDescription", testIngredients, "testInstructions", 10, testLevel) };
				vector<string> testSeries = { "testSeries" };
				vector<string> testExclude = { "testExclude" };
				RealmOfRecipes testRealm = RealmOfRecipes(testRecipes, 10, 3, 1, testSeries, testExclude);
				vector<Recipes> expectedRecipes = { Recipes("testName", "testSeries", "testDescription", testIngredients, "testInstructions", 10, testLevel) };
				int expectedTime = 10;
				int expectedDifficulty = 3;
				int expectedSort = 1;
				vector<string> expectedSeries = { "testSeries" };
				vector<string> expectedExclude = { "testExclude" };

				//Test
				Assert::AreEqual(testRealm.allRecipes.at(0).getName(), expectedRecipes.at(0).getName());
				Assert::AreEqual(testRealm.timeFilter, expectedTime);
				Assert::AreEqual(testRealm.difficultyFilter, expectedDifficulty);
				Assert::AreEqual(testRealm.sortFilter, expectedSort);
				Assert::AreEqual(testRealm.allSeries.at(0), expectedSeries.at(0));
				Assert::AreEqual(testRealm.excludedIngredients.at(0), expectedExclude.at(0));
			}




	
		};
}
