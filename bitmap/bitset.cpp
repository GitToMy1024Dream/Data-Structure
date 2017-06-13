#include "bitset.h"
#include <bitset>
void Test1()
{
	BitSet b1(123);
	cout << b1.Count() << endl;
	b1.Set(1);
	b1.Set(21);
	b1.Set(59);
	cout << b1.Count() << endl;
	b1.ReSet(1);
	b1.ReSet(21);
	b1.ReSet(59);
	cout << b1.Count() << endl;
}
int main()
{
	Test1();
	system("pause");
	return 0;
}