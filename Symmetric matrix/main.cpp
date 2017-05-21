#include "SymmetricMatrix.h"
void Func()
{
	int a[5][5] = { 0,1,2,3,4,
			        1,0,1,2,3,
			        2,1,0,1,2,
			        3,2,1,0,1,
			        4,3,2,1,0 };
	SymmetricMatrix<int> s((int*)a, 5);
	s.Display();
	cout << s.Access(0,1) << endl;
	cout << s.Access(1,0) << endl;
}
int main()
{
	Func();
	system("pause");
	return 0;
}