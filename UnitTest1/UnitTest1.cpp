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
			Assert::AreEqual(std::string("�����������"), determineTriangleType(3.0, 4.0, 5.0));

			// ���� �� ������������ ���������
			Assert::AreEqual(std::string("������������"), determineTriangleType(5.0, 5.0, 5.0));

			// ���� �� ������������ ���������
			Assert::AreEqual(std::string("������������"), determineTriangleType(5.0, 5.0, 8.0));

			// ���� �� ������������ ���������
			Assert::AreEqual(std::string("������������"), determineTriangleType(6.0, 7.0, 8.0));

			// ���� �� ����������� ���������
			Assert::AreEqual(std::string("�� � �����������"), determineTriangleType(1.0, 2.0, 3.0));
		}

		TEST_METHOD(TestCalculateDistance)
		{
			// ���� �� ������� �� �������
			Assert::AreEqual(5.0, calculateDistance(0.0, 0.0, 3.0, 4.0), 1e-9);
			Assert::AreEqual(0.0, calculateDistance(1.0, 1.0, 1.0, 1.0), 1e-9);
			Assert::AreEqual(10.0, calculateDistance(-5.0, 0.0, 5.0, 0.0), 1e-9);
		}

		
	};
}
