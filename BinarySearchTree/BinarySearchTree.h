#pragma once
#include <iostream>
#include <assert.h>
using namespace std;
template<class K, class V>
struct BinarySearchTreeNode
{
	BinarySearchTreeNode(const K& key, const V& value)
		: _pLeft(NULL)
		, _pRight(NULL)
		, _key(key)
		, _value(value)
	{}
	BinarySearchTreeNode<K, V>* _pLeft;
	BinarySearchTreeNode<K, V>* _pRight;
	K _key;
	V _value;
};
template<class K, class V>
class BinarySearchTree
{
	typedef BinarySearchTreeNode<K, V> Node;
public:
	BinarySearchTree()
		: _pRoot(NULL)
	{}
	Node* Find(const K& key)
	{
		return _Find(_pRoot, key);
	}

	bool Insert(const K& key, const V& value)
	{
		return _Insert(_pRoot, key, value);
	}

	bool Remove(const K& key)
	{
		return _Remove(_pRoot, key);
	}

	void InOrder()
	{
		cout << "InOrder: ";
		_InOrder(_pRoot);
		cout << endl;
	}
protected:
	//寻找值为key的结点
	Node* _Find(Node* pRoot, const K& key)
	{
		if (pRoot == NULL)
			return NULL;
		if (key < pRoot->_key)
			return _Find(pRoot->_pLeft, key);
		else if (key > pRoot->_key)
			return _Find(pRoot->_pRight, key);
	}
	//插入
	bool _Insert(Node* & pRoot, const K& key, const V& value)
	{
		if (pRoot == NULL)
		{
			pRoot = new Node(key, value);
			return true;
		}
		if (key < pRoot->_key)
		{
			return _Insert(pRoot->_pLeft, key, value);
		}
		else if (key > pRoot->_key)
		{
			return _Insert(pRoot->_pRight, key, value);
		}
		else
			return false;
	}
	//删除
	bool _Remove(Node*& pRoot, const K& key)
	{
		if (pRoot == NULL)
			return false;
		if (key < pRoot->_key)
			return _Remove(pRoot->_pLeft, key);
		else if (key > pRoot->_key)
			return _Remove(pRoot->_pRight, key);
		else
		{
			Node* pCur = pRoot;
			if (pRoot->_pLeft == NULL)
				pRoot = pRoot->_pRight;
			else if (pRoot->_pRight == NULL)
				pRoot = pRoot->_pLeft;
			else
			{
				Node* MinNodeFromRight = pRoot->_pRight;
				Node* pParent = pRoot;
				while (MinNodeFromRight->_pLeft)
				{
					pParent = MinNodeFromRight;
					MinNodeFromRight = MinNodeFromRight->_pLeft;
				}
				pRoot->_key = MinNodeFromRight->_key;
				pRoot->_value = MinNodeFromRight->_value;
				pCur = MinNodeFromRight;
				if (pParent->_pLeft == MinNodeFromRight)
				{
					pParent->_pLeft = MinNodeFromRight->_pRight;
				}
				else if (pParent->_pRight == MinNodeFromRight)
				{
					pParent->_pRight = MinNodeFromRight->_pRight;
				}
			}
			delete pCur;
			return true;
		}
	}
	//中序遍历
	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_key << " ";
			_InOrder(pRoot->_pRight);
		}
	}
protected:
	Node* _pRoot;
};