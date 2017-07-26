#include "bloom.h"
void FunTest()
{
	BloomFilter<int> bf;
	bf.Set(1001);
	bf.Set(2001);
	bf.Set(3939);
	cout << bf.IsIn(1001) << endl;
	cout << bf.IsIn(2001) << endl;
	cout << bf.IsIn(3939) << endl;
}
int main()
{
	FunTest();
	system("pause");
	return 0;
}