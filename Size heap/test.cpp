//test.cpp
#include "heap.h"
void Test()
{
	int Array[] = { 3 ,4 ,6 ,5 ,7 ,2 };
	Myheap<int,Greate<int>> _h(Array,sizeof(Array)/sizeof(Array[0]));
	cout << _h.Size() << endl;
	cout << _h.Top() << endl;
	_h.PushHeap(2);
	cout << _h.Size() << endl;
	cout << _h.Top() << endl;
	Myheap<int, Less<int>> _h1(Array, sizeof(Array) / sizeof(Array[0]));
	cout << _h1.Size() << endl;
	cout << _h1.Top() << endl;
	_h1.PushHeap(2);
	cout << _h1.Size() << endl;
	cout << _h1.Top() << endl;
	_h1.PopHeap();
	cout << _h1.Size() << endl;
	cout << _h1.Top() << endl;
	
}
int main()
{
	Test();
	system("pause");
	return 0;
}