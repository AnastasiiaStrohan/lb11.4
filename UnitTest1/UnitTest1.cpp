#include "pch.h"
#include "CppUnitTest.h"
#include "../lb11.4/lb11.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Assert::AreEqual(std::string("прямокутний"), determineTriangleType(3.0, 4.0, 5.0));

			// Тест на рівносторонній трикутник
			Assert::AreEqual(std::string("рівносторонній"), determineTriangleType(5.0, 5.0, 5.0));

			// Тест на рівнобедрений трикутник
			Assert::AreEqual(std::string("рівнобедрений"), determineTriangleType(5.0, 5.0, 8.0));

			// Тест на різносторонній трикутник
			Assert::AreEqual(std::string("різносторонній"), determineTriangleType(6.0, 7.0, 8.0));

			// Тест на некоректний трикутник
			Assert::AreEqual(std::string("не є трикутником"), determineTriangleType(1.0, 2.0, 3.0));
		}

		TEST_METHOD(TestCalculateDistance)
		{
			// Тест на відстань між точками
			Assert::AreEqual(5.0, calculateDistance(0.0, 0.0, 3.0, 4.0), 1e-9);
			Assert::AreEqual(0.0, calculateDistance(1.0, 1.0, 1.0, 1.0), 1e-9);
			Assert::AreEqual(10.0, calculateDistance(-5.0, 0.0, 5.0, 0.0), 1e-9);
		}

		
	};
}
