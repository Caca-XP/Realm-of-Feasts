#include "pch.h"
#include "CppUnitTest.h"
#include "../../src/Support.h"

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
	};
}