bool IsLoop(ListNode* pHead)
{
	if (pHead == NULL)
		return false;
	ListNode* pSlow = pHead->next;//慢指针一次走一步
	if (pSlow == NULL)
		return false;
	ListNode* pFast = pSlow->next;//快指针一次走两步
	while (pFast != NULL && pSlow != NULL)
	{
		if (pFast == pSlow)
			return true;
		pSlow = pSlow->next;
		pFast = pFast->next;
		if (pFast != NULL)
		{
			pFast = pFast->next;
		}
		return false;
	}
}