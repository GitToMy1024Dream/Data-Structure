#include <iostream>
using namespace std;

struct ListNode
{
	int _value;
	ListNode* _pnext;
};

ListNode* deleteDuplication(ListNode** pHead)
{
	if (pHead == NULL || *pHead == NULL)
		return NULL;
	ListNode* prev = NULL;
	ListNode* pnode = *pHead;
	while (pnode != NULL)
	{
		ListNode* pnext = pnode->_pnext;
		bool needDelete = false;
		if (pnext != NULL && pnode->_value == pnext->_value)
		{
			needDelete = true;
		}
		if (!needDelete)
		{
			prev = pnode;
			pnode = pnext;
		}
		else
		{
			int value = pnode->_value;
			ListNode* tobeDelete = pnode;
			while (tobeDelete != NULL && tobeDelete->_value == value)
			{
				pnext = tobeDelete->_pnext;
				delete tobeDelete;
				tobeDelete = NULL;
				tobeDelete = pnext;
			}
			if (prev == NULL)
				*pHead = pnext;
			else
				prev->_pnext = pnext;
			pnode = pnext;
		}
	}
}

int main()
{
	system("pause");
	return 0;
}