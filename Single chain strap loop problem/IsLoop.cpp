bool IsLoop(ListNode* pHead)
{
	if (pHead == NULL)
		return false;
	ListNode* pSlow = pHead->next;//��ָ��һ����һ��
	if (pSlow == NULL)
		return false;
	ListNode* pFast = pSlow->next;//��ָ��һ��������
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