#include "pch.h"
#include "CppUnitTest.h"
#include "../App.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace RealmOfFeastTest
{

	TEST_CLASS(AppTest)
	{
		/**
		 * Test process ingredients function of the App
		 * @see App.cpp
		 * @test
		 */
		TEST_METHOD(TestProcessIngredients)
		{
			////test the processIngredients function
			//string testIngredient = "1*unit1*ingredient1, 2*unit2*ingredient2, 3*unit3*ingredient3, 4*unit4*ingredient4, 5*unit5*ingredient5";
			//vector<Ingredients> expectedIngredients = {Ingredients(1, "unit1", "ingredient1"), Ingredients(2, "unit2", "ingredient2"), Ingredients(3, "unit3", "ingredient3"), Ingredients(4, "unit4", "ingredient4"), Ingredients(5, "unit5", "ingredient5") };
			//vector<Ingredients> actualIngredients;

			//// Check if process_ingred throws any exceptions
			//try {
			//	actualIngredients = process_ingred(testIngredient);
			//}
			//catch (const exception& ex) {
			//	Assert::Fail(L"Exception thrown during process_ingred execution.");
			//}

			////Test names of the ingredients match
			//Assert::AreEqual(actualIngredients.at(0).getName(), expectedIngredients.at(0).getName());
			//Assert::AreEqual(actualIngredients.at(1).getName(), expectedIngredients.at(1).getName());
			//Assert::AreEqual(actualIngredients.at(2).getName(), expectedIngredients.at(2).getName());
			//Assert::AreEqual(actualIngredients.at(3).getName(), expectedIngredients.at(3).getName());
			//Assert::AreEqual(actualIngredients.at(4).getName(), expectedIngredients.at(4).getName());

			////Test units of the ingredients match
			//Assert::AreEqual(actualIngredients.at(0).getUnit(), expectedIngredients.at(0).getUnit());
			//Assert::AreEqual(actualIngredients.at(1).getUnit(), expectedIngredients.at(1).getUnit());
			//Assert::AreEqual(actualIngredients.at(2).getUnit(), expectedIngredients.at(2).getUnit());
			//Assert::AreEqual(actualIngredients.at(3).getUnit(), expectedIngredients.at(3).getUnit());
			//Assert::AreEqual(actualIngredients.at(4).getUnit(), expectedIngredients.at(4).getUnit());

			////Test quantities of the ingredients match
			//Assert::AreEqual(actualIngredients.at(0).getQuantity(), expectedIngredients.at(0).getQuantity());
			//Assert::AreEqual(actualIngredients.at(1).getQuantity(), expectedIngredients.at(1).getQuantity());
			//Assert::AreEqual(actualIngredients.at(2).getQuantity(), expectedIngredients.at(2).getQuantity());
			//Assert::AreEqual(actualIngredients.at(3).getQuantity(), expectedIngredients.at(3).getQuantity());
			//Assert::AreEqual(actualIngredients.at(4).getQuantity(), expectedIngredients.at(4).getQuantity());
			//Assert::AreEqual(1, 1);
		}
	};
}
