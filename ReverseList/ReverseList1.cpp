//有头结点
typedef struct ListNode 
{
	TypeDate Value;
	ListNode* pNext;
};
ListNode* ReverseList(ListNode* pHead)
{
	if (pHead == NULL || pHead->pNext == NULL)
	{
		return pHead;
	}
	ListNode* pRev = NULL;
	ListNode* pCur = pHead;
	while (pCur != NULL)
	{
		ListNode* pTemp = pCur;   
		pCur = pCur->pNext;       
		pTemp->pNext = pRev;      
		pRev = pTemp;
	}
	return pRev;
}