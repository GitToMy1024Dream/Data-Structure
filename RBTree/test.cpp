#include "RBTree.h"
void Test()
{
	RBTree<int, int> rb;
	int arr[] = {10, 7, 8, 15, 5, 6, 11, 13, 12};
	for (size_t idx = 0; idx < sizeof(arr) / sizeof(arr[0]); ++idx)
	{
		rb.Insert(arr[idx],idx);
	}
	rb.InOrder();
	if (rb.CheckRBTree())
		cout << "ÊÇºìºÚÊ÷." << endl;
	else
		cout << "²»ÊÇºìºÚÊ÷." << endl;
	if (rb.Find(7))
		cout << "Find Success." << endl;
	else
		cout << "Not Find." << endl;
	if (rb.Find(15))
		cout << "Find Success." << endl;
	else
		cout << "Not Find." << endl;
	rb.InOrder();
}
int main()
{
	Test();
	system("pause");
	return 0;
}