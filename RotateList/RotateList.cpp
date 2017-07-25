#include <iostream>
using namespace std;

struct Node {
	int _value;
	Node* _pNext;
	Node(const int& data)
		:_value(data)
		,_pNext(NULL)
	{}
};
//获取链表的长度
size_t GetLength(Node *pHead)
{
	Node* pCur = pHead;
	size_t count = 0;
	while (pCur)
	{
		++count;
		pCur = pCur->_pNext;
	}
	return count;
}

//逆置单链表
Node* reverseList(Node* pHead, Node* pTail)
{
	Node* prev = NULL;
	Node* pNode = pHead;
	Node* pNewHead = NULL;
	//逆置前K个节点
	while (pNode != NULL && pNode != pTail)
	{
		Node* pNext = pNode->_pNext;
		//遍历到尾节点时标记为头结点
		if (pNext == pTail)
			pNewHead = pNode;
		//头插
		pNode->_pNext = prev;
		prev = pNode;
		pNode = pNext;
	}
	return pNewHead;
}
//旋转单链表
Node* RotateList(Node* pHead, size_t K)
{
	//非法情况
	if (GetLength(pHead) <= 0 || K > GetLength(pHead))
		return NULL;
	int _k = K; 
	Node* pTmp = pHead;
	//获取需要逆置单链表的尾节点
	while (K--)
	{
		pTmp = pTmp->_pNext;
	}
	//逆置pHead--pTmp之间的结点
	Node* prev = reverseList(pHead, pTmp);
	Node* pCur = prev;
	//获取逆置之后的尾节点
	while (--_k)
	{
		pCur = pCur->_pNext;
	}	
	//与未逆置链表连接起来
	pCur->_pNext = pTmp;
	return prev;
}


//打印单链表
void PrintList(Node* pHead)
{
	Node* pCur = pHead;
	while (pCur)
	{
		cout << pCur->_value << "->";
		pCur = pCur->_pNext;
	}
	cout << "NULL" << endl;

}
void CreateList()
{
	Node* node1 = new Node(10);
	Node* node2 = new Node(20);
	Node* node3 = new Node(30);
	Node* node4 = new Node(40);
	Node* node5 = new Node(50);
	node1->_pNext = node2;
	node2->_pNext = node3;
	node3->_pNext = node4;
	node4->_pNext = node5;
	node5->_pNext = NULL;
	Node* head = RotateList(node1,2);
	PrintList(head);
}
int main()
{
	CreateList();
	system("pause");
	return 0;
}