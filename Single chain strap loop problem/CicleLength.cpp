ListNode* EntryNodeOfLoop(ListNode* pHead)
{
	ListNode* MeetNode = MeetingNode(pHead);//两个指针的相遇点
	if (MeetNode == NULL)
		return NULL;
	int NodesInLoop = 1;
	ListNode* pNode1 = MeetNode;
	while (pNode1->next != MeetNode)
	{
		pNode1 = pNode1->next;
		++NodesInLoop;//环的长度
	}
	pNode1 = pHead;
	for (int idx = 0; idx < MeetNode; ++idx)
	{
		pNode1 = pNode1->next;
	}
	ListNode* pNode2 = pHead;
	while (pNode1 != pNode2)
	{
		pNode1 = pNode1->next;
		pNode2 = pNode2->next;
	}
	return pNode1;//环的入口点