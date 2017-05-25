#include "BinaryTree_Thd.h"
void FunTest()
{
	int arr[] = { 1 ,2 ,3 ,'#' ,'#' ,'#' ,4 ,5 ,'#' ,'#' ,6 };
	BinaryTreeThd<int> _b(arr,sizeof(arr)/sizeof(arr[0]),'#');
	//_b.PreThread();
	//_b.InThread();
	_b.PostThread();
	//_b.PreOrder();
	//_b.InOrder();
	_b.PostOrder();
}
int main()
{
	FunTest();
	system("pause");
	return 0;
}