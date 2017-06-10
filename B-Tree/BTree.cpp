#include "BTree.h"
void Test1()
{
	BTree<int, 3> _bt;
	_bt.Insert(10);
	_bt.Insert(30);
	_bt.Insert(20);
	_bt.Insert(40);
	_bt.Insert(50);
	_bt.Insert(38);
	_bt.Insert(35);
	_bt.InOrder();
}
int main()
{
	Test1();
	system("pause");
	return 0;
}