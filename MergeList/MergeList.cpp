struct ListNode
{
	int data;
	ListNode* pNext;
};
ListNode* MergeList(ListNode* pHead1, ListNode* pHead2)
{
	if (pHead1 == NULL)
		return pHead2;
	else if (pHead2 == NULL)
		return pHead1;
	ListNode* MergeHead = NULL;
	if (pHead1->data < pHead2->data)
	{
		MergeHead = pHead1;
		MergeHead->pNext = MergeList(pHead1->pNext, pHead2);
	}
	else
	{
		MergeHead = pHead2;
		MergeHead->pNext = MergeList(pHead1, pHead2->pNext);
	}
	return MergeHead;
}
