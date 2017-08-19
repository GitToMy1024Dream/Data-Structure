#pragma once
#include <iostream>
using namespace std;

typedef struct ListNode
{
	int _data;
	ListNode* _pnext;
	ListNode(const int& data)
		:_data(data)
		,_pnext(NULL)
	{}
}Node;

//判断链表是否带环
Node* HasCicle(Node* pHead)
{
	if (pHead == NULL)
		return NULL;
	Node* pSlow = pHead;
	Node* pFast = pHead;
	while (pFast && pFast->_pnext)
	{
		pFast = pFast->_pnext->_pnext;
		pSlow = pSlow->_pnext;
		if (pSlow == pFast)
			return pSlow;
	}
	return NULL;
}

//单链表中环的长度
size_t GetCircleLength(Node* pHead)
{
	int len = 1;
	Node* meet = NULL;
	if (meet = HasCicle(pHead))
	{
		Node* pCur = meet->_pnext;
		while (pCur != meet)
		{
			++len;
			pCur = pCur->_pnext;
		}
	}
	return len;
}

//环的入口点
Node* EntryCicle(Node* pHead)
{
	if (pHead == NULL || pHead->_pnext == NULL)
		return NULL;
	Node* meet = HasCicle(pHead);
	Node* pNode = pHead;
	while (meet != pNode)
	{
		meet = meet->_pnext;
		pNode = pNode->_pnext;
	}
	return pNode;
}

//判断两个链表是否相交(都不带环)
bool IsIntersected(Node* pHead1, Node* pHead2)
{
	if (pHead1 == NULL || pHead2 == NULL)
		return false;
	Node* pNode1 = pHead1;
	Node* pNode2 = pHead2;
	while (pNode1->_pnext)
		pNode1 = pNode1->_pnext;
	while (pNode2->_pnext)
		pNode2 = pNode2->_pnext;
	if (pNode1 == pNode2)
		return true;
	return false;
}
//链表带环，判断是否相交
bool IsIntersectedCicle(Node* pHead1, Node* pHead2)
{
	if (pHead1 == NULL || pHead2 == NULL)
		return false;
	Node* meet1 = HasCicle(pHead1);
	Node* meet2 = HasCicle(pHead2);
	if (meet1 == meet2)
		return true;
	Node* pCur = meet1->_pnext;
	while (pCur != meet1 && pCur != meet2)
	{
		pCur = pCur->_pnext;
	}
	if (pCur == meet2)
		return true;
	else
		return false;
}


//交点
Node* GetFirstCommonNode(Node* pHead1, Node* pHead2)
{
	if (pHead1 == NULL || pHead2 == NULL)
		return false;
	int len1 = 0;
	Node* pNode1 = pHead1;
	while (pNode1)
	{
		++len1;
		pNode1 = pNode1->_pnext;
	}
	int len2 = 0;
	Node* pNode2 = pHead2;
	while (pNode2)
	{
		++len2;
		pNode2 = pNode2->_pnext;
	}
	int sub = len1 - len2;
	pNode1 = pHead1;
	pNode2 = pHead2;
	if (sub > 0)
	{
		while (sub--)
			pNode1 = pNode1->_pnext;
	}
	else if (sub < 0)
	{
		sub = 0 - sub;
		while (sub--)
			pNode2 = pNode2->_pnext;
	}
	while (pNode1 != pNode2)
	{
		pNode1 = pNode1->_pnext;
		pNode2 = pNode2->_pnext;
	}
	return pNode1;
}