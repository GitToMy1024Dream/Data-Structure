
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
	ListNode* pCur = pHead->pNext;
	ListNode* pNet = NULL;
	pHead->pNext = NULL;
	while (pCur)
	{
		pNet = pCur->pNext;//���浱ǰ�ڵ����һ���ڵ�
		pCur->pNext = pHead->pNext;//�ѽڵ���뵽pHead�ĺ���
		pHead->pNext = pHead;//��pHeadָ�����µĽڵ�
		pCur = pNet;
	}
}