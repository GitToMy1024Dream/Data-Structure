#pragma once
#include <iostream>
#include <cstdlib>
#include <assert.h>
using namespace std;
#pragma warning (disable:4996)
template<class K, class V>
struct AVLTreeNode//AVL树的结构
{
	AVLTreeNode(const K& key, const V& value)
		: _pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
		, _key(key)
		, _value(value)
		, _bf(0)
	{}
	AVLTreeNode<K, V> *_pLeft;
	AVLTreeNode<K, V> *_pRight;
	AVLTreeNode<K, V> *_pParent;
	K _key;
	V _value;
	int _bf;       // 平衡因子：right-left
};
 
template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	//构造函数
	AVLTree()
		: _pRoot(NULL)
	{}
	//析构函数
	~AVLTree()
	{
		DestroyTree(_pRoot);
	}
	//插入
	bool Insert(const K& key, const V& value)
	{
		if (_pRoot == NULL)//空树
		{
			_pRoot = new Node(key, value);
			return true;
		}
		Node* pCur = _pRoot;
		Node* pParent = NULL;
		//寻找插入位置
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
				return false;
		}
		pCur = new Node(key, value);
		//判断插入位置是当前双亲的左孩子或右孩子
		if (key < pParent->_key)
		{
			pParent->_pLeft = pCur;
			pCur->_pParent = pParent;
		}
		else
		{
			pParent->_pRight = pCur;
			pCur->_pParent = pParent;
		}
		//更新平衡因子
		while (pParent)
		{
			if (pParent->_pLeft == pCur)
				pParent->_bf--;
			else
				pParent->_bf++;
			//pParent有左孩子或右孩子
			if (pParent->_bf == 0)
				return true;
			//pParent是叶子结点
			else if (pParent->_bf == 1 || pParent->_bf == -1)
			{
				pCur = pParent;
				pParent = pParent->_pParent;
			}
			//4种特殊情况
			else if (pParent->_bf == -2 || pParent->_bf == 2)
			{
				if (pParent->_bf == 2)
				{
					if (pCur->_bf == 1)//同号
					{
						_RotateL(pParent);//左旋
						return true;
					}
					else//异号
					{
						_RotateRL(pParent);//右左双旋
						return true;
					}
				}
				else if (pParent->_bf == -2)
				{
					if (pCur->_bf == 1)//异号
					{
						_RotateLR(pParent);//左右双旋
						return true;
					}
					else//同号
					{
						_RotateR(pParent);//右旋
						return true;
					}
				}
			}
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
	//获取树的高度
	size_t Height()
	{
		return _Height(_pRoot);
	}
	//判断二叉树是否平衡
	bool IsBalanceTree()
	{
		return _IsBalanceTree(_pRoot);
	}
	//销毁
	Node* DestroyTree(Node*& pRoot)
	{
		if (pRoot != NULL)
		{
			DestroyTree(pRoot->_pLeft);
			DestroyTree(pRoot->_pRight);
			delete pRoot;
			pRoot = NULL;
		}
		return pRoot;
	}
private:
	//判断是否平衡
	bool _IsBalanceTree(Node* pRoot)
	{
		if (pRoot == NULL)
			return false;
		size_t height = abs((long)(_Height(pRoot->_pRight) - _Height(pRoot->_pLeft)));
		return (height < 2) && (_IsBalanceTree(pRoot->_pLeft)) && (_IsBalanceTree(pRoot->_pRight));
	}
	//树的高度
	size_t _Height(Node* pRoot)
	{
		if (pRoot == NULL)
			return 0;
		size_t leftHeight = _Height(pRoot->_pLeft) + 1;
		size_t rightHeight = _Height(pRoot->_pRight) + 1;
		return leftHeight > rightHeight ? leftHeight : rightHeight;
	}
	//中序递归打印(最好用stack)
	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_key << " ";
			_InOrder(pRoot->_pRight);
		}
	}
	//左单旋
	void _RotateL(Node* pParent)
	{
		assert(pParent);
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		pParent->_pRight = pSubRL;
		if (pSubRL)
		{
			pSubRL->_pParent = pParent;
		}
		Node* ppParent = pParent->_pParent;
		pSubR->_pLeft = pParent;
		pParent->_pParent = pSubR;
		//根节点的双亲是否存在
		if (ppParent == NULL)
		{
			_pRoot = pSubR;
			pSubR->_pParent = NULL;
		}
		//根节点的双亲存在
		else
		{
			if (ppParent->_pLeft == pSubR)
			{
				ppParent->_pLeft = pSubR;
			}
			else
				ppParent->_pRight = pSubR;
			pSubR->_pParent = ppParent;
		}
		pParent->_bf = pSubR->_bf = 0;//将平衡因子置0
	}
	//右单旋
	void _RotateR(Node* pParent)
	{
		assert(pParent);
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		pParent->_pLeft = pSubLR;
		if (pSubLR)
		{
			pSubLR->_pParent = pParent;
		}
		Node* ppParent = pParent->_pParent;
		pSubL->_pRight = pParent;
		pParent->_pParent = pSubL;
		//根节点的双亲是否存在
		if (ppParent == NULL)
		{
			_pRoot = pSubL;
			pSubL->_pParent = NULL;//将平衡因子置0
		}
		//根节点的双亲存在
		else
		{
			if (ppParent->_pLeft == pSubL)
			{
				ppParent->_pLeft = pSubL;
			}
			else
				ppParent->_pRight = pSubL;
			pSubL->_pParent = ppParent;
			
		}
		pParent->_bf = pSubL->_bf = 0;
	}
	//左右双旋
	void _RotateLR(Node* pParent)
	{
		assert(pParent);
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		int bf = pSubLR->_bf;
		_RotateL(pSubL);
		_RotateR(pParent);
		//bf = 0，则pSubLR为插入的结点
		if (bf == 0)
		{
			pSubL->_bf = pParent->_bf = 0;
		}
		//bf = 1，证明插入点是pSubLR的右孩子
		if (bf == 1)
		{
			pSubL->_bf = -1;
			pParent->_bf = 0;
		}
		//bf = -1，证明插入点是pSubLR的左孩子
		else
		{
			pSubL->_bf = 0;
			pParent->_bf = 1;
		}
		pSubLR->_bf = 0;
	}
	//右左双旋
	void _RotateRL(Node* pParent)
	{
		assert(pParent);
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		int bf = pSubRL->_bf;
		_RotateR(pSubR);
		_RotateL(pParent);
		//bf = 0，证明插入的结点为pSubRL
		if (bf == 0)
		{
			pParent->_bf = pSubR->_bf = 0;
		}
		//bf = 1，插入的结点为pSubRL的右孩子
		if (bf == 1)
		{
			pSubR->_bf = 0;
			pParent->_bf = -1;
		}
		//bf = -1,插入的结点为pSubRL的左孩子
		else
		{
			pSubR->_bf = 1;
			pParent->_bf = 0;
		}
		pSubRL->_bf = 0;
	}
private:
	Node* _pRoot;
};