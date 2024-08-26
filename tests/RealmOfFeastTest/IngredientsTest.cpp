#include "pch.h"
#include "CppUnitTest.h"
#include "../../src/Ingredients.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RealmOfFeastTest
{
	TEST_CLASS(IngredientsTest)
	{
	public:

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
			std::string actualName = testIngredient.getName();
			std::string actualUnit = testIngredient.getUnit();
			double actualQuantity = testIngredient.getQuantity();

			//Test
			Assert::AreEqual(actualName, expectedName);
			Assert::AreEqual(actualUnit, expectedUnit);
			Assert::AreEqual(actualQuantity, expectedQuantity);
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
			std::string actualName = testIngredient.getName();
			std::string actualUnit = testIngredient.getUnit();
			double actualQuantity = testIngredient.getQuantity();

			//Test
			Assert::AreEqual(actualName, expectedName);
			Assert::AreEqual(actualUnit, expectedUnit);
			Assert::AreEqual(actualQuantity, expectedQuantity);
		}
	};
}