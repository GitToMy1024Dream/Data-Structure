#pragma once
#include <iostream>
#include <assert.h>
using namespace std;
typedef struct BinaryTreeNode
{
	int m_value;//当前节点的值
	BinaryTreeNode* m_pLeft;//指向左孩子的指针
	BinaryTreeNode* m_pRight;//指向右孩子的指针
}Node;
Node* ConstructCore(int* startPre, int* endPre, int* startIn, int* endIn);
Node* Construct(int* PreOrder, int* InOrder, int length)
{
	if (PreOrder == NULL || InOrder == NULL || length <= 0)
		return NULL;
	//传入的4个参数为:
	//前序序列的首元素下标,前序序列的尾元素的下标
	//中序序列的首元素下标,中序序列的尾元素的下标
	return ConstructCore(PreOrder, PreOrder + length - 1,
		InOrder, InOrder + length - 1);
}
Node* ConstructCore(int* startPre, int* endPre, int* startIn, int* endIn)
{
	//前序遍历的第一个数字即根节点的值
	int rootValue = startPre[0];
	Node* root = new Node();
	root->m_value = rootValue;
	root->m_pLeft = root->m_pRight = NULL;
        //仅有一个节点的情况
	if (startPre == endPre)
	{
		if (startIn == endIn && *startPre == *startIn)
			return root;
		else
			throw std::exception("invalid input");
	}
	//在中序遍历中扎到根节点的值
	int* rootInOrder = startIn;
	while (rootInOrder <= endIn && rootValue != *rootInOrder)
		++rootInOrder;
	if (rootInOrder == endIn && *rootInOrder != rootValue)
		throw std::exception("Invalid input.");
	int leftLength = rootInOrder - startIn;//
	int* leftPreOrderEnd = startPre + leftLength;//
	if (leftLength > 0)//左子树存在
	{
		//构建左子树
		root->m_pLeft = ConstructCore(startPre+1,leftPreOrderEnd,startIn,rootInOrder - 1);
	}
	   //构建右子树
           //左子树的个数小于元素的总个数(右子树存在)
	if (leftLength < (endPre - startPre))
	{
		root->m_pRight = ConstructCore(leftPreOrderEnd+1,endPre,rootInOrder+1,endIn);
	}
	return root;
}