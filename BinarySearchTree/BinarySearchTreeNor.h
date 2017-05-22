#pragma once
#include <iostream>
#include <assert.h>
#include <vector>
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

// 非递归版本
template<class K, class V>
class BinarySearchTree
{
	typedef BinarySearchTreeNode<K, V> Node;
public:
	BinarySearchTree()
		: _pRoot(NULL)
	{}
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
		if (_pRoot)
			Destroy(_pRoot);//销毁
	}
	//查找值为key的结点
	Node* Find(const K& key)
	{
		if (_pRoot == NULL)
			return NULL;
		Node* pCur = _pRoot;
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
		if (_pRoot == NULL)
		{
			_pRoot = new Node(key,value);
			return true;
		}
		Node* pCur = _pRoot;
		Node* Parent = NULL;
		//寻找插入位置
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
		Node* NewNode = new Node(key, value);
		//判断插入的结点是双亲结点的左孩子还是右孩子
		if (key < Parent->_key)
		{
			Parent->_pLeft = NewNode;
		}
		else if (key > Parent->_key)
		{
			Parent->_pRight = NewNode;
		}
		return false;
	}
	//删除
	bool Remove(const K& key)
	{
		if (_pRoot == NULL)//空树
			return false;
		if (_pRoot->_pLeft == NULL && _pRoot->_pRight == NULL
			&& _pRoot->_key == key)//只有根节点
			return true;
		Node* pCur = _pRoot;
		Node* pParent = NULL;
		//寻找删除节点的位置
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
		//左为空
		if (pCur->_pLeft == NULL)
		{
			//如果删除的是根节点
			if (pParent == NULL)
			{
				_pRoot = pCur->_pRight;
			}
			//图2所示情况
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
			//图3所示情况
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
			//寻找右子树中序遍历的第一个节点
			while (MinNodeFromRight->_pLeft)
			{
				pParent = MinNodeFromRight;
				MinNodeFromRight = MinNodeFromRight->_pLeft;
			}
			//将中序遍历的第一个节点的信息赋值给双亲pCur
			pCur->_key = MinNodeFromRight->_key;
			pCur->_value = MinNodeFromRight->_value;
			//图4所示情况
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
		return true;
	}
	//中序遍历
	void InOrder()
	{
		cout << "InOrder: ";
		_InOrder(_pRoot);
		cout << endl;
	}
	//获取最小结点
	const K& GetMaxKey()const
	{
		if (_pRoot == NULL)
			return NULL;
		Node* pCur = _pRoot;
		while (pCur->_pRight)
		{
			pCur = pCur->_pRight;
		}
		return pCur->_key;
	}
	//获取最大结点
	const K& GetMinKey()const
	{
		if (_pRoot == NULL)
			return NULL;
		Node* pCur = _pRoot;
		while (pCur->_pLeft)
		{
			pCur = pCur->_pLeft;
		}
		return pCur->_key;
	}

protected:
	Node* Copy(Node* pRoot)//前序构造二叉树
	{
		Node* pCur = pRoot;
		if (pCur)
		{
			pCur = new Node(pRoot->_key,pRoot->_value);
			pCur->_pLeft = Copy(pRoot->_pLeft);
			pCur->_pRight = Copy(pRoot->_pRight);
		}
		return pCur;
	}
	//后序销毁二叉树
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
	Node* _pRoot;
};
