#include "BinaryTree.h"
void Test()
{
	int arr[] = { 1 ,2 ,3 ,'#','#',4 ,'#','#',5 , 6 };
	BinaryTree<int> _b1(arr, sizeof(arr) / sizeof(arr[0]), '#');
	BinaryTree<int> _b2 = _b1;
	BinaryTree<int> _b3(_b1);
	cout << _b1.IsCompleteTree() << endl;
	/*_b1.PreOrder();
	_b1.InOrder();
	_b1.PostOrder();
	_b1.LevelOrder();
	cout << "Depth:" << _b1.Depth() << endl;
	cout << "Size:" << _b1.Size() << endl;
	cout << "Find:" << _b1.FindData(1) << endl;
	cout << "LeefCount:" << _b1.GetLeefCount() << endl;
	cout << "GetKlevelCount:" << _b1.GetKLevelCount(3) << endl;
	_b2.PreOrder();
	_b2.InOrder();
	_b2.PostOrder();
	_b2.LevelOrder();
	cout << "Size:" << _b2.Size() << endl;
	_b3.PreOrder();
	_b3.InOrder();
	_b3.PostOrder();
	_b3.LevelOrder();
	cout << "Size:" << _b3.Size() << endl;
	_b1.BinaryMirror();
	_b1.PreOrder();
	_b1.InOrder();
	_b1.PostOrder();
	_b1.LevelOrder();*/
}
int main()
{
	Test();
	system("pause");
	return 0;
}