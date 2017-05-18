#pragma once
#include <iostream>
#include <assert.h>
using namespace std;
typedef struct BinaryTreeNode
{
	int m_value;//��ǰ�ڵ��ֵ
	BinaryTreeNode* m_pLeft;//ָ�����ӵ�ָ��
	BinaryTreeNode* m_pRight;//ָ���Һ��ӵ�ָ��
}Node;
Node* ConstructCore(int* startPre, int* endPre, int* startIn, int* endIn);
Node* Construct(int* PreOrder, int* InOrder, int length)
{
	if (PreOrder == NULL || InOrder == NULL || length <= 0)
		return NULL;
	//�����4������Ϊ:
	//ǰ�����е���Ԫ���±�,ǰ�����е�βԪ�ص��±�
	//�������е���Ԫ���±�,�������е�βԪ�ص��±�
	return ConstructCore(PreOrder, PreOrder + length - 1,
		InOrder, InOrder + length - 1);
}
Node* ConstructCore(int* startPre, int* endPre, int* startIn, int* endIn)
{
	//ǰ������ĵ�һ�����ּ����ڵ��ֵ
	int rootValue = startPre[0];
	Node* root = new Node();
	root->m_value = rootValue;
	root->m_pLeft = root->m_pRight = NULL;
        //����һ���ڵ�����
	if (startPre == endPre)
	{
		if (startIn == endIn && *startPre == *startIn)
			return root;
		else
			throw std::exception("invalid input");
	}
	//������������������ڵ��ֵ
	int* rootInOrder = startIn;
	while (rootInOrder <= endIn && rootValue != *rootInOrder)
		++rootInOrder;
	if (rootInOrder == endIn && *rootInOrder != rootValue)
		throw std::exception("Invalid input.");
	int leftLength = rootInOrder - startIn;//
	int* leftPreOrderEnd = startPre + leftLength;//
	if (leftLength > 0)//����������
	{
		//����������
		root->m_pLeft = ConstructCore(startPre+1,leftPreOrderEnd,startIn,rootInOrder - 1);
	}
	   //����������
           //�������ĸ���С��Ԫ�ص��ܸ���(����������)
	if (leftLength < (endPre - startPre))
	{
		root->m_pRight = ConstructCore(leftPreOrderEnd+1,endPre,rootInOrder+1,endIn);
	}
	return root;
}