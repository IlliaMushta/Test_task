#include "pch.h"
#include "CppUnitTest.h"
#include "..\DataStructures\dataStruct.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataStructuresTests
{
	TEST_CLASS(DataStructuresTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			List<int> myList;
			Assert::IsTrue(myList.getSize() == 0, L"Assert1");
		}

		TEST_METHOD(TestMethod2)
		{
			List<int> myList;
			myList.push_back(5);
			Assert::IsTrue(myList.getSize() == 1, L"Assert2");
		}

		TEST_METHOD(TestMethod3)
		{
			List<int> myList;
			myList.push_back(5);
			myList.pop_back();
			Assert::IsTrue(myList.getSize() == 0, L"Assert3");
		}

		TEST_METHOD(TestMethod4)
		{
			List<int> myList;
			myList.push_front(5);
			myList.pop_front();
			Assert::IsTrue(myList.getSize() == 0, L"Assert4");
		}

		TEST_METHOD(TestMethod5)
		{
			List<int> myList;
			myList.push_front(5);
			Assert::IsTrue(myList.getSize() == 1, L"Assert5");
		}

		TEST_METHOD(TestMethod6)
		{
			List<int> myList;
			myList.push_front(5);
			myList.removeAt(0);
			Assert::IsTrue(myList.getSize() == 0, L"Assert6");
		}

		TEST_METHOD(TestMethod7)
		{
			List<int> myList;
			myList.push_front(5);
			myList.push_front(6);
			myList.push_front(15);
			myList.push_front(7);
			myList.push_front(9);
			myList.clear();
			Assert::IsTrue(myList.getSize() == 0, L"Assert7");
		}

		TEST_METHOD(TestMethod8)
		{
			Self_Balancing_Binary_Tree<int> myTree;
			Assert::IsTrue(myTree.Size() == 0, L"Assert8");
		}

		TEST_METHOD(TestMethod9)
		{
			Self_Balancing_Binary_Tree<int> myTree;
			myTree.InsertNode(5);
			Assert::IsTrue(myTree.Height() == 1, L"Assert9");
		}

		TEST_METHOD(TestMethod10)
		{
			Self_Balancing_Binary_Tree<int> myTree;
			myTree.InsertNode(5);
			myTree.Clear();
			Assert::IsTrue(myTree.Height() == 0, L"Assert10");
		}

		TEST_METHOD(TestMethod11)
		{
			Self_Balancing_Binary_Tree<int> myTree;
			myTree.InsertNode(5);
			myTree.InsertNode(4);
			myTree.InsertNode(7);
			myTree.InsertNode(2);
			myTree.InsertNode(1);
			Assert::IsTrue(myTree.Height() <=1 && myTree.Height() >= 1, L"Assert11");
		}
	};
}