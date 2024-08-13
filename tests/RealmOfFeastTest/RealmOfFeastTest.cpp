#include "pch.h"
#include "CppUnitTest.h"
#include "../../App.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RealmOfFeastTest
{
	TEST_CLASS(RealmOfFeastTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(1, 1);
		}

		TEST_METHOD(TestRecipesDefaultConstructor)
		{
			Recipes testRecipe = Recipes();
			std::string expectedName = "";
			std::string expectedSeries = "";
			std::string expectedDescription = "";
			std::string expectedInstructions = "";



			//Test
			Assert::AreEqual(testRecipe.getName(), expectedName);
			Assert::AreEqual(testRecipe.getSeries(), expectedSeries);
			Assert::AreEqual(testRecipe.getDescription(), expectedDescription);
			Assert::AreEqual(testRecipe.getInstructions(), expectedInstructions);

		}
	};
}
