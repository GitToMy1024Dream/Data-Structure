//��ͷ���
 
typedef struct ListNode
{
	TypeDate value;
	ListNode* pNext;
};
ListNode* ReverseList(ListNode* pHead)
{
	if (pHead == NULL || pHead->pNext == NULL)
		return pHead;
//3��ָ��ֱ�ָ��ǰ3���ڵ�
	ListNode* pPre = pHead;
	ListNode* pCur = pPre->pNext;
	ListNode* pNet = pCur->pNext;
	while (pNet)
	{
		pCur->pNext = pPre;
		pPre = pCur;
		pCur = pNet;
		pNet = pNet->pNext;
	}
	pCur->pNext = pPre;//���һ���ڵ㴦��
	pHead->pNext = NULL;
	return pCur;
}