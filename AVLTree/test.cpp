#include "AVLTree.h"
void TestAVL()
{
	//int array[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
	int array[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	AVLTree<int, int> t;
	for (size_t idx = 0; idx < sizeof(array) / sizeof(array[0]); ++idx)
		t.Insert(array[idx], idx);
	t.InOrder();
	if (t.IsBalanceTree())
	{
		cout << "ÊÇAVLÊ÷" << endl;
	}
	else
	{
		cout << "²»ÊÇAVLÊ÷" << endl;
	}
}
int main()
{
	TestAVL();
	system("pause");
	return 0;
}