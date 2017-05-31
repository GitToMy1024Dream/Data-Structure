ListNode* MeetingNode(ListNode* pHead)
{
	if (pHead == NULL)
		return NULL;
	ListNode* pSlow = pHead->next;
	if (pSlow == NULL)
		return NULL;
	ListNode* pFast = pSlow->next;
	while (pFast != NULL && pSlow != NULL)
	{
		if (pFast == pSlow)
			return pFast;
		pSlow = pSlow->next;
		pFast = pFast->next;
		if (pFast != NULL)
			pFast = pFast->next;
	}
	return NULL;
}