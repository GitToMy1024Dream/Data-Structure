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
//��ȡ����ĳ���
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

//���õ�����
Node* reverseList(Node* pHead, Node* pTail)
{
	Node* prev = NULL;
	Node* pNode = pHead;
	Node* pNewHead = NULL;
	//����ǰK���ڵ�
	while (pNode != NULL && pNode != pTail)
	{
		Node* pNext = pNode->_pNext;
		//������β�ڵ�ʱ���Ϊͷ���
		if (pNext == pTail)
			pNewHead = pNode;
		//ͷ��
		pNode->_pNext = prev;
		prev = pNode;
		pNode = pNext;
	}
	return pNewHead;
}
//��ת������
Node* RotateList(Node* pHead, size_t K)
{
	//�Ƿ����
	if (GetLength(pHead) <= 0 || K > GetLength(pHead))
		return NULL;
	int _k = K; 
	Node* pTmp = pHead;
	//��ȡ��Ҫ���õ������β�ڵ�
	while (K--)
	{
		pTmp = pTmp->_pNext;
	}
	//����pHead--pTmp֮��Ľ��
	Node* prev = reverseList(pHead, pTmp);
	Node* pCur = prev;
	//��ȡ����֮���β�ڵ�
	while (--_k)
	{
		pCur = pCur->_pNext;
	}	
	//��δ����������������
	pCur->_pNext = pTmp;
	return prev;
}


//��ӡ������
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