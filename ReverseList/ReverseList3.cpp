
//有头结点
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
		pNet = pCur->pNext;//保存当前节点的下一个节点
		pCur->pNext = pHead->pNext;//把节点插入到pHead的后面
		pHead->pNext = pHead;//让pHead指向最新的节点
		pCur = pNet;
	}
}