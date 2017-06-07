#pragma once
#include <iostream>
#include <assert.h>
using namespace std;
enum COLOR
{
	RED,
	BLACK
};
template<class K,class V>
struct RBTreeNode
{
	RBTreeNode* _pLeft;
	RBTreeNode* _pRight;
	RBTreeNode* _pParent;
	K _key;
	V _value;
	int _color;
	RBTreeNode(const K& key = K(), const V& value = V(), const COLOR& color = RED)
		:_pLeft(NULL)
		, _pRight(NULL)
		, _pParent(NULL)
		, _key(key)
		, _value(value)
		, _color(color)
	{}
};
template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	//构造函数
	RBTree()
		:_pRoot(NULL)
	{}
	//析构函数
	~RBTree()
	{
		_pRoot = _Destory(_pRoot);
	}
	//拷贝构造函数
	RBTree(const RBTree<K, V>& rb)
	{
		if (it != &rb)
		{
			_pRoot = _Copy(_pRoot);
		}
	}
	//赋值运算符的重载
	RBTree<K, V> operator=(const RBTree<K, V>& rb)
	{
		if (*it != rb)
		{
			Node* tmp = _Copy(rb->_pRoot);
			_pRoot = _Destroy(_pRoot);
			_pRoot = tmp;
		}
		return *this;
	}
	//插入
	bool Insert(const K& key, const V& value)
	{
		if (_pRoot == NULL)
		{
			_pRoot = new Node(key, value);
			_pRoot->_color = BLACK;
			return true;
		}
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
				return false;
		}
		pCur = new Node(key, value);
		if (key < pParent->_key)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;
		pCur->_pParent = pParent;		
		//未调整到根节点且父节点还是红色
		while (pCur != _pRoot && pParent->_color == RED)
		{
			Node* ppParent = pParent->_pParent;
			//先处理左边
			if (ppParent->_pLeft == pParent)
			{
				Node* uncle = pParent->_pRight;
				//1.叔叔存在且为红色
				if (uncle && uncle->_color == RED)
				{
					pParent->_color = uncle->_color = BLACK;
					ppParent->_color = RED;
					pCur = ppParent;
					pParent = pCur->_pParent;
				}
				//2.叔叔不存在或者叔叔为黑色
				else
				{
					//3.pCur为pParent的右孩子
					if (pParent->_pRight == pCur)
					{
						_RotaeL(pParent);
						std::swap(pCur,pParent);
					}
					//2.pCur为pParent的左孩子
					else
					{
						_RotaeR(ppParent);
						ppParent->_color = RED;
						pParent->_color = BLACK;
					}
				}
			}
			//再处理右边的情况(与上述情况刚好位置相反)
			else
			{
				Node* uncle = ppParent->_pLeft;
				//4.叔叔存在且为红
				if (uncle && uncle->_color == RED)
				{
					pParent->_color = uncle->_color = BLACK;
					pCur->_color = RED;
					pCur = ppParent;
					pParent = pCur->_pParent;
				}
				//5.叔叔不存在或者叔叔为黑色
				else
				{
					//6.pCur为pParent的左孩子
					if (pParent->_pLeft == pCur)
					{
						_RotaeR(pParent);
						std::swap(pCur, ppParent);
					}
					//5.pCur为pParent的右孩子
					else
					{
						_RotaeL(ppParent);
						ppParent->_color = RED;
						pParent->_color = BLACK;
					}
				}
			}
		}
		_pRoot->_color = BLACK;
		return true;
	}
	//判断是否为红黑树
	bool CheckRBTree()
	{
		//空树肯定是红黑树
		if (_pRoot == NULL)
			return true;
		//性质1：根节点为红必然不是红黑树
		if (_pRoot->_color == RED)
			return false;
		size_t count = 0;
		Node* pCur = _pRoot;
		while (pCur)
		{
			if (pCur->_color == BLACK)
				count++;
			pCur = pCur->_pLeft;
		}
		size_t k = 0;
		_CheckRBTree(_pRoot, count, k);
	}
	//查找
	bool Find(const K& key)
	{
		if (_pRoot == NULL)
			return false;
		Node* pCur = _pRoot;
		while (pCur)
		{
			if (key < pCur->_key)
				pCur = pCur->_pLeft;
			else if (key > pCur->_key)
				pCur = pCur->_pRight;
			else
				return true;
		}
		return false;
	}
	//中序遍历
	void InOrder()
	{
		_InOrder(_pRoot);
		cout << endl;
	}
protected:
	//判断是否红黑树
	bool _CheckRBTree(Node* pRoot, const size_t& count, size_t K)
	{
		if (pRoot == NULL)
			return true;
		//性质2：两个相邻的结点都为红色
		if (pRoot->_pParent && pRoot->_color == pRoot->_pParent->_color == RED)
			return false;
		//性质3：从根节点到叶子结点的每条路径上的黑色节点一样
		if (pRoot->_color == BLACK)
			K++;
		//到达叶子结点进行比较
		if (pRoot->_pLeft == NULL && pRoot->_pRight == NULL)
		{
			if (count == K)
				return true;
			else
				return false;
		}
		return _CheckRBTree(pRoot->_pLeft, count, K) && _CheckRBTree(pRoot->_pRight, count, K);
	}
	//拷贝
	Node* _Copy(Node* pRoot)
	{
		Node* pCur = pRoot;
		if (pCur)
		{
			pCur = new Node(pRoot->_key, pRoot->_value);
			pCur->_pLeft = _Copy(pRoot->_pLeft);
			pCur->_pRight = _Copy(pRoot->_pRight);
		}
		return pCur;
	}
	//销毁
	Node* _Destory(Node* pRoot)
	{
		if (pRoot)
		{
			pRoot->_pLeft = _Destory(pRoot->_pLeft);
			pRoot->_pRight = _Destory(pRoot->_pRight);
			delete pRoot;
			pRoot = NULL;
		}
		return pRoot;
	}
	//左旋
	void _RotaeL(Node* pParent)
	{
		assert(pParent);
		//较高右子树的右侧插入
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		pParent->_pRight = pSubRL;
		if (pSubRL)
		{
			pSubRL->_pParent = pParent;
		}
		Node* ppParent = pParent->_pParent;
		pSubR->_pRight = pParent;
		pParent->_pParent = pSubR;
		//ppParent不存在
		if (ppParent == NULL)
		{
			_pRoot = pSubR;
			pSubR->_pParent = NULL;
		}
		//ppParent存在
		else
		{
			if (ppParent->_pLeft == pParent)
			{
				ppParent->_pLeft = pSubR;
			}
			else
			{
				ppParent->_pRight = pSubR;
			}
			pSubR->_pParent = ppParent;
		}
	}
	//右旋
	void _RotaeR(Node* pParent)
	{
		assert(pParent);
		//较高左子树的左侧插入
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
			pSubL->_pParent = NULL;
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
private:
	Node* _pRoot;
};
