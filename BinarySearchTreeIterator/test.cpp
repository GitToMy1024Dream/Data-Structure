#pragma once
#include <iostream>
#include <assert.h>
#include <vector>
using namespace std;
template<class K, class V>
struct BinarySearchTreeNode
{
	BinarySearchTreeNode(const K& key = K(), const V& value = V())
		: _pLeft(NULL)
		, _pRight(NULL)
		,_pParent(NULL)
		, _key(key)
		, _value(value)
	{}
	BinarySearchTreeNode<K, V>* _pLeft;
	BinarySearchTreeNode<K, V>* _pRight;
	BinarySearchTreeNode<K, V>* _pParent;
	K _key;
	V _value;
};
template<class K,class V,class Ref,class Ptr>
class BinarySearchTreeIterator
{
	typedef BinarySearchTreeNode<K, V> Node;
	typedef BinarySearchTreeIterator<K, V, Ref, Ptr> Self;
public:
	BinarySearchTreeIterator()
		:_pNode(NULL)
	{}
	BinarySearchTreeIterator(Node* pNode)
		:_pNode(pNode)
	{}
	BinarySearchTreeIterator(const Self& s)
		:_pNode(s._pNode)
	{}
	//前置++
	Self& operator++()
	{
		Increment();
		return *this;
	}
	//后置++
	Self operator++(int)
	{
		Self temp(*this);
		Increment();
		return temp;
	}
	//前置--
	Self& operator--()
	{
		Decrement();
		return *this;
	}
	//后置--
	Self operator--(int)
	{
		Self temp(*this);
		Decrement();
		return temp;
	}
	//重载解引用*
	Ref operator*()
	{
		return _pNode->_key;
	}
	//重载间接访问符->
	Ptr operator->()
	{
		return &(operator*());
	}
	//重载！=
	bool operator!=(const Self& s)
	{
		return _pNode != s._pNode;
	}
	//重载==(与！=应该成对出现)
	bool operator==(const Self& s)
	{
		return !(_pNode != s._pNode);
	}
protected:
	//取当前节点的下一个节点
	void Increment()
	{
		//如果右子树存在，当前节点的下一个节点为右子树最小的结点
		if (_pNode->_pRight)
		{
			_pNode = _pNode->_pRight;
			while (_pNode->_pLeft)
				_pNode = _pNode->_pLeft;
		}
		else//右子树不存在
		{
			Node* pParent = _pNode->_pParent;
			while (pParent->_pRight == _pNode)
			{
				_pNode = pParent;
				pParent = pParent->_pParent;
			}
			//根节点的右子树不存在，获取根的下一个节点
			if(_pNode->_pRight != pParent)
				_pNode = pParent;
		}
	}
	//取当前节点的前一个节点
	void Decrement()
	{
		//左子树存在时：在左子树中找最大的结点
		if (_pNode->_pLeft)
		{
			_pNode = _pNode->_pLeft;
			while (_pNode->_pRight)
				_pNode = _pNode->_pRight;
		}
		//左子树不存在
		else
		{
			Node* pParent = _pNode->_pParent;
			while (pParent->_pLeft == _pNode)
			{
				_pNode = pParent;
				pParent = pParent->_pParent;
			}
			_pNode = pParent;
		}
	}
protected:
	Node* _pNode;
};

template<class K, class V>
class BinarySearchTree
{
	typedef BinarySearchTreeNode<K, V> Node;
public:
	typedef BinarySearchTreeIterator<K, V, K&, K*> Iterator;
	//构造函数
	BinarySearchTree()
	{
		pHead = new Node();
		pHead->_pLeft = pHead;
		pHead->_pRight = pHead;
		pHead->_pParent = NULL;
	}
	//拷贝构造函数
	BinarySearchTree(const BinarySearchTree& bst)
	{
		assert(bst._pRoot);
		_pRoot = Copy(bst._pRoot);
	}
	//赋值运算符的重载
	BinarySearchTree<K, V>& operator=(const BinarySearchTree<K, V>& bst)
	{
		if (this != &bst)
		{
			BinarySearchTree<K, V> tmp(bst);
			std::swap(tmp._pRoot, _pRoot);
		}
		return *this;
	}
	//析构函数
	~BinarySearchTree()
	{
		if (pHead)
			Destroy(pHead);
	}
	//首节点(二叉树中最左边的结点)
	Iterator Begin()
	{
		return pHead->_pLeft;
	}
	//尾节点(头结点)
	Iterator End()
	{
		return pHead;
	}
	//查找值为key的结点
	Node* Find(const K& key)
	{
		if (pHead == NULL)
			return NULL;
		Node* pCur = pHead->_pParent;
		while (pCur)
		{
			if (key < pCur->_key)
				pCur = pCur->_pLeft;
			else if (key > pCur->_key)
				pCur = pCur->_pRight;
			else
				return pCur;
		}
		return NULL;
	}
	//插入
	bool Insert(const K& key, const V& value)
	{
		Node*& _pRoot = pHead->_pParent;
		if (_pRoot == NULL)
		{
			_pRoot = new Node(key, value);
			_pRoot->_pParent = pHead;
		}
		else
		{
			Node* pCur = _pRoot;
			Node* Parent = NULL;
			while (pCur)
			{
				if (key < pCur->_key)
				{
					Parent = pCur;
					pCur = pCur->_pLeft;
				}
				else if (key > pCur->_key)
				{
					Parent = pCur;
					pCur = pCur->_pRight;
				}
				else
					return false;
			}
			pCur = new Node(key, value);
			if (key < Parent->_key)
			{
				Parent->_pLeft = pCur;
			}
			else if (key > Parent->_key)
			{
				Parent->_pRight = pCur;
			}
			pCur->_pParent = Parent;
		}
		pHead->_pLeft = LeftMin();
		pHead->_pRight = RightMax();
		return true;
	}
	bool Remove(const K& key)
	{
		Node*& _pRoot = GetRoot();
		if (_pRoot == NULL)
			return false;
		if (_pRoot->_pLeft == NULL && _pRoot->_pRight == NULL
			&& _pRoot->_key == key)
		{
			delete _pRoot;
			pHead->_pParent = NULL;
		}
		else
		{
			Node* pCur = _pRoot;
			Node* pParent = NULL;
			while (pCur)
			{
				if (key < pCur->_key)
				{
					pParent = pCur;
					pCur = pCur->_pLeft;
				}
				else if (key > pCur->_key)
				{
					pParent = pCur;
					pCur = pCur->_pRight;
				}
				else
					break;
			}
			if (pCur == NULL)
				return false;
			else
			{
				//左为空
				if (pCur->_pLeft == NULL)
				{
					//如果删除的是根节点
					if (pParent == NULL)
					{
						_pRoot = pCur->_pRight;
					}
					else
					{
						if (pParent->_pLeft == pCur)
						{
							pParent->_pLeft = pCur->_pRight;
						}
						else if (pParent->_pRight == pCur)
						{
							pParent->_pRight = pCur->_pRight;
						}
					}
					delete pCur;
				}
				//右为空，左不为空
				else if (pCur->_pRight == NULL)
				{
					//删除根节点
					if (pParent == NULL)
					{
						_pRoot = pCur->_pLeft;
					}
					else
					{
						if (pParent->_pLeft == pCur)
						{
							pParent->_pLeft = pCur->_pLeft;
						}
						else if (pParent->_pRight == pCur)
						{
							pParent->_pRight = pCur->_pLeft;
						}
					}
					delete pCur;
				}
				//左右都不为空
				else
				{
					pParent = pCur;
					Node* MinNodeFromRight = pCur->_pRight;
					while (MinNodeFromRight->_pLeft)
					{
						pParent = MinNodeFromRight;
						MinNodeFromRight = MinNodeFromRight->_pLeft;
					}
					pCur->_key = MinNodeFromRight->_key;
					pCur->_value = MinNodeFromRight->_value;
					if (pParent->_pLeft == MinNodeFromRight)
					{
						pParent->_pLeft = MinNodeFromRight->_pRight;
					}
					else
					{
						pParent->_pRight = MinNodeFromRight->_pRight;
					}
					delete MinNodeFromRight;
				}
			}
		}
		pHead->_pLeft = LeftMin();
		pHead->_pRight = RightMax();
		return true;
	}
	//中序遍历
	void InOrder()
	{
		cout << "InOrder: ";
		_InOrder(GetRoot());
		cout << endl;
	}
	//最大结点
	const K& GetMaxKey()const
	{
		Node* _pRoot = GetRoot();
		if (_pRoot == NULL)
			return NULL;
		Node* pCur = _pRoot;
		while (pCur->_pRight)
		{
			pCur = pCur->_pRight;
		}
		return pCur->_key;
	}
	//最小结点
	const K& GetMinKey()const
	{
		Node* _pRoot = GetRoot();
		if (_pRoot == NULL)
			return NULL;
		Node* pCur = _pRoot;
		while (pCur->_pLeft)
		{
			pCur = pCur->_pLeft;
		}
		return pCur->_key;
	}
	//最左边的结点
	Node* LeftMin()
	{
		Node* pCur = GetRoot();
		assert(pCur);
		while (pCur->_pLeft)
		{
			pCur = pCur->_pLeft;
		}
		return pCur;
	}
	//最右边的结点
	Node* RightMax()
	{
		Node* pCur = GetRoot();
		assert(pCur);
		while (pCur->_pRight)
		{
			pCur = pCur->_pRight;
		}
		return pCur;
	}
	//头结点
	Node*& GetRoot()
	{
		return pHead->_pParent;
	}
protected:
	//拷贝
	Node* Copy(Node* pRoot)
	{
		Node* pCur = pRoot;
		if (pCur)
		{
			pCur = new Node(pRoot->_key, pRoot->_value);
			pCur->_pLeft = Copy(pRoot->_pLeft);
			pCur->_pRight = Copy(pRoot->_pRight);
		}
		return pCur;
	}
	//销毁
	Node* Destroy(Node* pRoot)
	{
		if (pRoot)
		{
			pRoot->_pLeft = Destroy(pRoot->_pLeft);
			pRoot->_pRight = Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = NULL;
		}
		return pRoot;
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
	Node* pHead;
};