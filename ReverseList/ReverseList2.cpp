//无头结点
 
typedef struct ListNode
{
	TypeDate value;
	ListNode* pNext;
};
ListNode* ReverseList(ListNode* pHead)
{
	if (pHead == NULL || pHead->pNext == NULL)
		return pHead;
//3个指针分别指向前3个节点
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
	pCur->pNext = pPre;//最后一个节点处理
	pHead->pNext = NULL;
	return pCur;
}