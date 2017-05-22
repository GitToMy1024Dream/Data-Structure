#include "BinarySearchTree.h"
void Test1()
{
	int arr[] = { 5,7,3,1,2,0,9,8,6,4 };
	BinarySearchTree<int, int> bst;
	for (size_t idx = 0; idx < sizeof(arr) / sizeof(arr[0]); ++idx)
	{
		bst.Insert(arr[idx], idx);
	}
	bst.InOrder();
	cout << bst.GetMaxKey() << endl;
	cout << bst.GetMinKey() << endl;
	if (bst.Find(15))
	{
		cout << "Find Success!" << endl;
	}
	else
		cout << "Not Find!" << endl;
	/*BinarySearchTree<int, int> bst1 = bst;
	bst1.InOrder();*/
}
void Test2()
{
	int arr[] = { 5,7,3,1,2,0,8,9,6,4 };
	BinarySearchTree<int, int> bst;
	for (size_t idx = 0; idx < sizeof(arr) / sizeof(arr[0]); ++idx)
	{
		bst.Insert(arr[idx], idx);
	}
	bst.InOrder();
	//bst.Remove(5);
	//bst.Remove(6);
	//bst.Remove(2);
	//bst.Remove(7);
	//bst.Remove(0);
	bst.InOrder();
}
//void Test3()
//{
//	int arr[] = { 5,7,6,8 };
//	BinarySearchTree<int, int> bst;
//	for (size_t idx = 0; idx < sizeof(arr) / sizeof(arr[0]); ++idx)
//	{
//		bst.Insert(arr[idx], idx);
//	}
//	bst.InOrder();
//	bst.Remove(5);
//	bst.InOrder();
////}
//void Test4()
//{
//	int arr[] = { 5,3,7,1,4,8 };
//	BinarySearchTree<int, int> bst;
//	for (size_t idx = 0; idx < sizeof(arr) / sizeof(arr[0]); ++idx)
//	{
//		bst.Insert(arr[idx], idx);
//	}
//	bst.InOrder();
//	//bst.Remove(5);
//	//bst.InOrder();
//	BinarySearchTree<int, int> bst1(bst);
//	BinarySearchTree<int, int> bst2;
//	bst1.InOrder();
//	bst2 = bst1;
//	bst2.InOrder();
//}
void Test5()
{
	int arr[] = { 5,3,7,1,4,8 };
	vector<int> v(arr, arr + sizeof(arr) / sizeof(arr[0]));
	vector<int>::iterator it = v.begin();
	while (it != v.end())
	{
		cout << *it << " ";
		it++;
	}
}
int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	system("pause");
	return 0;
}