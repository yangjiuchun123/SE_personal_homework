#include "pch.h"
#include "CppUnitTest.h"
#include "../SE_hw1/SE_hw1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Solve *sol = new Solve(1);
			Line* l1 = new Line(0, 0, 1, 1);
			sol->addShape(l1);
			Assert::AreEqual(0, sol->getSolve());
		}

		TEST_METHOD(TestMethod2)	//平行的情况
		{
			Solve* sol = new Solve(1);
			Line* l1 = new Line(0, 0, 1, 1);
			Line* l2 = new Line(1, 2, 3, 4);
			sol->addShape(l1);
			sol->addShape(l2);
			Assert::AreEqual(0, sol->getSolve());
		}

		TEST_METHOD(TestMethod3)
		{
			Solve* sol = new Solve(2);
			Line* l1 = new Line(0, 0, 1, 1);
			Line* l2 = new Line(-1, 1, 1, -1);
			sol->addShape(l1);
			sol->addShape(l2);
			Assert::AreEqual(1, sol->getSolve());
		}

		TEST_METHOD(TestMethod4)
		{
			Solve* sol = new Solve(3);
			Line* l1 = new Line(0, 0, 1, 1);
			Line* l2 = new Line(-1, 1, 1, -1);
			Line* l3 = new Line(-100000, 100000, 100000, 100000);
			sol->addShape(l1);
			sol->addShape(l2);
			sol->addShape(l3);
			Assert::AreEqual(3, sol->getSolve());
		}

		TEST_METHOD(TestMethod5)
		{
			Solve* sol = new Solve(4);
			Line* l1 = new Line(0, 0, 1, 1);
			Line* l2 = new Line(-1, 1, 1, -1);
			Line* l3 = new Line(-100000, 100000, 100000, 100000);
			Line* l4 = new Line(-1, 100000, 2, -100000);
			sol->addShape(l1);
			sol->addShape(l2);
			sol->addShape(l3);
			sol->addShape(l4);
			Assert::AreEqual(6, sol->getSolve());
		}

		TEST_METHOD(TestMethod6)
		{
			Solve* sol = new Solve(5);
			Line* l1 = new Line(0, 0, 1, 1);
			Line* l2 = new Line(-1, 1, 1, -1);
			Line* l3 = new Line(-100000, 100000, 100000, 100000);
			Line* l4 = new Line(-1, 100000, 2, -100000);
			Circle* c1 = new Circle(0, 5, 1);
			sol->addShape(l1);
			sol->addShape(l2);
			sol->addShape(l3);
			sol->addShape(l4);
			sol->addShape(c1);
			Assert::AreEqual(8, sol->getSolve());
		}

		TEST_METHOD(TestMethod7)
		{
			Solve* sol = new Solve(5);
			Line* l1 = new Line(0, 0, 1, 1);
			Line* l2 = new Line(-1, 1, 1, -1);
			Line* l3 = new Line(-100000, 100000, 100000, 100000);
			Line* l4 = new Line(-1, 100000, 2, -100000);
			Circle* c1 = new Circle(0, 5, 100000);
			sol->addShape(l1);
			sol->addShape(l2);
			sol->addShape(l3);
			sol->addShape(l4);
			sol->addShape(c1);
			Assert::AreEqual(14, sol->getSolve());
		}

		TEST_METHOD(TestMethod8)	//多个直线与圆交于一点
		{
			Solve* sol = new Solve(4);
			Line* l1 = new Line(0, 1, 1, 1);
			Line* l2 = new Line(1, 0, 1, -1);
			Circle* c1 = new Circle(1, 2, 1);
			Circle* c2 = new Circle(1, 0, 1);
			sol->addShape(l1);
			sol->addShape(l2);
			sol->addShape(c1);
			sol->addShape(c2);
			Assert::AreEqual(3, sol->getSolve());
		}

		TEST_METHOD(TestMethod9)
		{
			Solve* sol = new Solve(4);
			Line* l1 = new Line(0, 1, 0, 0);
			Line* l2 = new Line(2, 0, 2, -1);
			Circle* c1 = new Circle(1, 2, 1);
			Circle* c2 = new Circle(1, 0, 1);
			sol->addShape(l1);
			sol->addShape(l2);
			sol->addShape(c1);
			sol->addShape(c2);
			Assert::AreEqual(5, sol->getSolve());
		}

		TEST_METHOD(TestMethod10)
		{
			Solve* sol = new Solve(4);
			Line* l1 = new Line(0, 1, 0, 0);
			Line* l2 = new Line(2, 0, 2, -1);
			Circle* c1 = new Circle(1, 2, 1);
			Circle* c2 = new Circle(1, 0, 1);
			sol->addShape(l1);
			sol->addShape(l2);
			sol->addShape(c1);
			sol->addShape(c2);
			Assert::AreEqual(5, sol->getSolve());
		}

		TEST_METHOD(TestMethod11)
		{
			Solve* sol = new Solve(3);
			Circle* c1 = new Circle(1, 0, 1);
			Circle* c2 = new Circle(-1, 0, 1);
			Circle* c3 = new Circle(0, 1, 1);
			sol->addShape(c1);
			sol->addShape(c2);
			sol->addShape(c3);
			Assert::AreEqual(3, sol->getSolve());
		}

		TEST_METHOD(TestMethod12)
		{
			Solve* sol = new Solve(5);
			Line* l1 = new Line(0, 0, 1, 1);
			Line* l2 = new Line(-1, 1, 1, -1);
			Circle* c1 = new Circle(1, 0, 1);
			Circle* c2 = new Circle(-1, 0, 1);
			Circle* c3 = new Circle(0, 1, 1);
			sol->addShape(l1);
			sol->addShape(l2);
			sol->addShape(c1);
			sol->addShape(c2);
			sol->addShape(c3);
			Assert::AreEqual(5, sol->getSolve());
		}

	};
}
