#include "BinaryTree.h"
void Func()
{
	int PreOrder[] = { 1,2,3,4,5,6 };
	int InOrder[] = { 3,2,1,5,4,6 };
	BinaryTree<int> _b1;
	_b1.Rebuild(PreOrder, InOrder, sizeof(PreOrder) / sizeof(PreOrder[0]));
}
int main()
{
	Func();
	system("pause");
	return 0;
}