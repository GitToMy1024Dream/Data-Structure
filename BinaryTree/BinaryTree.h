#pragma once
#include <iostream>
#include <assert.h>
#include <queue>
#include <stack>
using namespace std;
template<class T>
struct BinaryTreeNode//构造节点
{
	T m_nValue;//当前节点的值
	BinaryTreeNode<T>* m_pLeft;//指向左孩子的指针
	BinaryTreeNode<T>* m_pRight;//指向右孩子的指针
	BinaryTreeNode(const T& data)
		:m_nValue(data)
		, m_pLeft(NULL)
		, m_pRight(NULL)
	{}
};
template<class T>
class BinaryTree//二叉树的基本操作
{
	
public:
	typedef BinaryTreeNode<T> Node;
	//不带参数的构造函数
	BinaryTree();
	//带4个参数的构造函数
	BinaryTree(T *arr, size_t size, const T& invalid);
	//拷贝构造函数
	BinaryTree(BinaryTree<T>& _b);
	//赋值运算符的重载
	BinaryTree<T>& operator=(BinaryTree<T>& s);
	//析构函数
	~BinaryTree();
	//创建二叉树
	Node* CreateTree(T* arr, size_t size, const T& invalid, size_t& index)
	{
		Node* pRoot = NULL;
		if (index < size)
		{
			//按照先序遍历构造二叉树
			if (arr[index] != invalid)
			{
				pRoot = new Node(arr[index]);
				pRoot->m_pLeft = CreateTree(arr, size, invalid, ++index);
				pRoot->m_pRight = CreateTree(arr, size, invalid, ++index);
			}
		}
		return pRoot;
	}
	//拷贝二叉树
	Node* Copy(Node* pRoot)
	{
		Node* pCur = pRoot;
		if (pCur)
		{
			//①先拷贝根节点
			//②拷贝左子树
			//③拷贝右子树
			pCur = new Node(pRoot->m_nValue);
			pCur->m_pLeft = Copy(pRoot->m_pLeft);
			pCur->m_pRight = Copy(pRoot->m_pRight);
		}
		return pCur;
	}
	//释放二叉树的结点
	Node* Destroy(Node* pRoot)
	{
		if (pRoot)
		{
			//①先释放左子树
			//②再释放右子树
			//③最后释放根节点
			pRoot->m_pLeft = Destroy(pRoot->m_pLeft);
			pRoot->m_pRight = Destroy(pRoot->m_pRight);
			delete pRoot;
			pRoot = NULL;
		}
		return pRoot;
	}
	//前序遍历递归
	void _PreOrder(Node* pRoot);
	//前序遍历非递归
	void _PreOrder_Nor(Node* pRoot);
	//中序遍历
	void _InOrder(Node* pRoot);
	//中序遍历非递归(栈)
	void _InOrder_Nor(Node* pRoot);
	//后序遍历
	void _PostOrder(Node* pRoot);
	//后序遍历非递归(栈)
	void _PostOrder_Nor(Node* pRoot);
	//层序遍历(队列)
	void _LevelOrder(Node* pRoot);
	void PreOrder();
	void InOrder();
	void PostOrder();
	void LevelOrder();
	//二叉树中结点的个数
	size_t Size();
	size_t _Size(Node* pRoot);
	//二叉树的深度
	size_t Depth();
	size_t _Depth(Node* pRoot);
	//查找值为data的结点
	Node* FindData(const T& data)
	{
		return _Find(_root, data);
	}
	Node* _Find(Node* pRoot, const T& data)
	{
		if (pRoot == NULL)
			return NULL;
		if (pRoot->m_nValue == data)
		{
			cout << "寻找成功:";
			return pRoot;
		}
		//递归左子树寻找data
		Node* pTmp = _Find(pRoot->m_pLeft, data);
		//若左子树不存在
		if (pTmp == NULL)
		{
			//再右子树中遍历寻找
			pTmp = _Find(pRoot->m_pRight, data);
		}
		return pTmp;
	}
	//查找Node结点的左孩子
	Node* GetLeftChild(Node* pCur)
	{
		return (pCur == NULL) ? NULL : pCur->m_pLeft;
	}
	//查找Node结点的右孩子
	Node* GetRightChild(Node* pCur)
	{
		return (pCur == NULL) ? NULL : pCur->m_pRight;
	}
	//查找Node结点的双亲结点
	Node* GetParent(Node* pCur)
	{
		return _GetParent(_root, pCur);
	}
	Node* _GetParent(Node* pRoot, Node* pCur)
	{
		if (pRoot == NULL || (pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL))
			return NULL;
		else
		{
			Node* pTmp = NULL;
			if (pTmp = _GetParent(pRoot->m_pLeft))
				return pTmp;
			if (pTmp = _GetParent(pRoot->m_pRight))
				return pTmp;
		}
	}
	//获取第K层结点的个数
	size_t GetKLevelCount(size_t K);
	size_t _GetKLevelCount(Node* pRoot, size_t K);
	//获取叶子结点的个数
	size_t GetLeefCount();
	size_t _GetLeefCount(Node* pRoot);
	//二叉树的镜像
	void BinaryMirror();
	void _BinaryMirror(Node* pRoot);
	//判断一个二叉树是否为完全二叉树
	bool IsCompleteTree();
	bool _IsCompleteTree(Node* pRoot);
	//寻找两节点的最近公共祖先
	Node* FindRecentParent(Node* data1, Node* data2)
	{
		return _FindRecentParent(_root,data1,data2);
	}
	//获取Node结点的路径
	bool _GetPath(Node* pRoot, Node* pCur, stack<Node*>& s)
	{
		if (pRoot == NULL || pCur == NULL)
			return false;
		s.push(pRoot);
		while (pCur->m_nValue == pRoot->m_nValue)
			return true;
		if (_GetPath(pCur->m_pLeft, pCur, s))
			return true;
		if (_GetPath(pCur->m_pRight, pCur, s))
			return true;
		s.pop();
		return false;
	}
	Node* _FindRecentParent(Node*& pRoot,Node* data1,Node* data2)
	{
		if (pRoot == NULL)
			return NULL;
		stack<Node*> _s1;
		stack<Node*> _s2;
		_GetPath(pRoot,data1,_s1);
		_GetPath(pRoot,data2,_s2);
		while (_s1.size() > _s2.size)
			_s1.pop();
		while (_s2.size() > _s1.size)
			_s2.pop();
		while (_s1.top != _s2.top())
		{
			_s1.pop();
			_s2.pop();
		}
		return _s1.top();
	}
private:
	Node* _root;
};

template<class T>
BinaryTree<T>::BinaryTree()
	:_root(NULL)
{}

template<class T>
BinaryTree<T>::BinaryTree(T *arr, size_t size, const T& invalid)
{
	assert(arr);
	size_t index = 0;
	_root = CreateTree(arr, size, invalid, index);
}
template<class T>
BinaryTree<T>::BinaryTree(BinaryTree<T>& _b)
{
	assert(_b._root);
	_root = Copy(_b._root);
}

template<class T>
BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree<T>& s)
{
	if (this != &s)
	{
		BinaryTree<T> tmp(s);
		std::swap(tmp._root, _root);
	}
	return *this;
}

template<class T>
BinaryTree<T>::~BinaryTree()
{
	if (_root)
		_root = Destroy(_root);
}

//前序遍历递归
template<class T>
void BinaryTree<T>::_PreOrder(Node* pRoot)
{
	if (pRoot)
	{
		cout << pRoot->m_nValue << " ";//先访问当前节点
		_PreOrder(pRoot->m_pLeft);//递归当前节点的左子树
		_PreOrder(pRoot->m_pRight);//递归当前节点的右子树
	}
}

//前序遍历非递归(使用栈)
template<class T>
void BinaryTree<T>::_PreOrder_Nor(Node* pRoot)
{
	//前提：栈不为空
	//①root入栈
	//②保存栈顶元素
	//③出栈
	//④访问右子树，若存在，入栈
	//⑤访问左子树，若存在，入栈
	if (pRoot == NULL)
		return;
	stack<Node*> _s;
	_s.push(pRoot);
	while (!_s.empty())
	{
		Node* _Top = _s.top();
		cout << _Top->m_nValue << " ";
		_s.pop();
		if (_Top->m_pRight)
			_s.push(_Top->m_pRight);
		if (_Top->m_pLeft)
			_s.push(_Top->m_pLeft);
	}
}

//中序遍历递归
template<class T>
void BinaryTree<T>::_InOrder(Node* pRoot)
{
	if (pRoot)
	{
		_InOrder(pRoot->m_pLeft);//先递归左子树
		cout << pRoot->m_nValue << " ";//在访问当前节点
		_InOrder(pRoot->m_pRight);//最后递归右子树
	}
}


//中序遍历非递归(使用栈)
template<class T>
void BinaryTree<T>::_InOrder_Nor(Node* pRoot)
{
	Node* pCur = pRoot;
	stack<Node*> _s;
	//栈不为空或者当前节点不为空，即树未遍历完
	while (!_s.empty() || pCur)
	{
		//将树的左节点(直到最左节点)全部压入栈内
		while (pCur)
		{
			_s.push(pCur);
			pCur = pCur->m_pLeft;
		}
		Node* _Top = _s.top();//保存当前栈顶元素
		cout << _Top->m_nValue << " ";//访问栈顶元素即根节点
		_s.pop();//将根节点出栈
		pCur = _Top->m_pRight;//以子问题的方法去访问右子树
	}
}

//后序遍历递归
template<class T>
void BinaryTree<T>::_PostOrder(Node* pRoot)
{
	if (pRoot)
	{
		_PostOrder(pRoot->m_pLeft);//先递归左子树
		_PostOrder(pRoot->m_pRight);//再递归右子树
		cout << pRoot->m_nValue << " ";//最后访问当前节点
	}
}
//后序遍历非递归(使用栈)
template<class T>
void BinaryTree<T>::_PostOrder_Nor(Node* pRoot)
{
	if (pRoot == NULL)
		return;
	stack<Node*> _s;
	Node* pCur = pRoot;
	Node* pMark = NULL;//标记是否访问过此节点的指针
	//栈不为空或者当前节点不为空，即树未遍历完
	while (!_s.empty() || pCur)
	{
		//将树的左节点(直到最左节点)全部压入栈内
		while (pCur)
		{
			_s.push(pCur);
			pCur = pCur->m_pLeft;
		}
		Node* _Top = _s.top();//取栈顶元素
		//如果栈顶元素(根节点)的右子树为空或者已经访问过
		if (_Top->m_pRight == NULL || _Top->m_pRight == pMark)
		{
			cout << _Top->m_nValue << " ";
			pMark = _Top;//用Mark标记此节点已经被访问
			_s.pop();
		}
		else//未访问右子树(与左子树类似)
		{
			pCur = _Top->m_pRight;//继续访问右子树
		}
	}
}

//层序遍历(使用队列)
template<class T>
void BinaryTree<T>::_LevelOrder(Node* pRoot)
{
	queue<Node*> _q;
	if (pRoot)
		_q.push(pRoot);//根节点入栈
	while (!_q.empty())//栈不为空
	{
		Node* front = _q.front();//保存队头元素
		cout << front->m_nValue << " ";
		_q.pop();//出队列
		if (front->m_pLeft)//左孩子存在入队列
			_q.push(front->m_pLeft);
		if (front->m_pRight)//右孩子存在入队列
			_q.push(front->m_pRight);
	}
}

template<class T>
void BinaryTree<T>::PreOrder()
{
	cout << "PreOrder:  ";
	//_PreOrder(_root);
	_PreOrder_Nor(_root);
	cout << endl;
}

template<class T>
void BinaryTree<T>::InOrder()
{
	cout << "InOrder:   ";
	//_InOrder(_root);
	_InOrder_Nor(_root);
	cout << endl;
}

template<class T>
void BinaryTree<T>::PostOrder()
{
	cout << "PostOrder: ";
	//_PostOrder(_root);
	_PostOrder_Nor(_root);
	cout << endl;
}

template<class T>
void BinaryTree<T>::LevelOrder()
{
	cout << "LevelOrder:";
	_LevelOrder(_root);
	cout << endl;
}

//二叉树中结点的个数
template<class T>
size_t BinaryTree<T>::Size()
{
	return _Size(_root);
}
template<class T>
size_t BinaryTree<T>::_Size(Node* pRoot)
{
	if (pRoot == NULL)//树为空
		return 0;
	else//树不为空时，节点个数为根节点+左子树节点+右孩子节点
		return 1 + _Size(pRoot->m_pLeft) + _Size(pRoot->m_pRight);
}


//树的深度
template<class T>
size_t BinaryTree<T>::Depth()
{
	return _Depth(_root);
}
template<class T>
size_t BinaryTree<T>::_Depth(Node* pRoot)
{
	if (pRoot == NULL)
		return 0;
	//树不为空时,定义左子树的高度left与右子树的高度right
	size_t left = 1;
	size_t right = 1;
	left += _Depth(pRoot->m_pLeft);//左子树存在+1，不存在+0
	right += _Depth(pRoot->m_pRight);//右子树存在+1，不存在+0
	return left > right ? left : right;//返回二者的较大者
}

//树种第K层节点的个数
template<class T>
size_t BinaryTree<T>::GetKLevelCount(size_t K)
{
	return _GetKLevelCount(_root, K);
}
template<class T>
size_t BinaryTree<T>::_GetKLevelCount(Node* pRoot, size_t K)
{
	
	if (pRoot == NULL || K < 1)//非法情况
		return 0;
	if (K == 1)//根节点为第1层
		return 1;
	//问题转换成第K-1层的左右子树结点的个数
	return _GetKLevelCount(pRoot->m_pLeft, K - 1) + _GetKLevelCount(pRoot->m_pRight, K - 1);
}

//树中叶子结点的个数
template<class T>
size_t BinaryTree<T>::GetLeefCount()
{
	return _GetLeefCount(_root);
}
template<class T>
size_t BinaryTree<T>::_GetLeefCount(Node* pRoot)
{
	if (pRoot == NULL)//空树
		return 0;
	if (pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL)//只有根节点
		return 1;
	//递归调用左子树的叶子结点+右子树的叶子结点
	return _GetLeefCount(pRoot->m_pLeft) + _GetLeefCount(pRoot->m_pRight);
}


//二叉树的镜像(左右子树交换位置)
template<class T>
void BinaryTree<T>::BinaryMirror()
{
	return _BinaryMirror(_root);
}
template<class T>
void BinaryTree<T>::_BinaryMirror(Node* pRoot)
{
	if (pRoot == NULL)
		return;
	std::swap(pRoot->m_pLeft, pRoot->m_pRight);//交换当前左右子树的结点
	_BinaryMirror(pRoot->m_pLeft);//遍历下一个左子树
	_BinaryMirror(pRoot->m_pRight);//遍历下一个右子树
}

//判断二叉树是否为完全二叉树
template<class T>
bool BinaryTree<T>::IsCompleteTree()
{
	return _IsCompleteTree(_root);
}
template<class T>
bool BinaryTree<T>::_IsCompleteTree(Node* pRoot)
{
	if (pRoot == NULL)
		return false;
	bool flag = true;
	queue<Node*> _q;
	_q.push(pRoot);
	while (!_q.empty())
	{
		Node* front = _q.front();
		_q.pop();
		if (front->m_pLeft == NULL)
		{
			flag = false;
		}
		else
		{
			if (flag == false)
				return false;
			_q.push(front->m_pLeft);
		}
		if (front->m_pRight == NULL)
		{
			flag = false;
		}
		else
		{
			if (flag == false)
				return false;
			_q.push(front->m_pRight);
		}
	}
	return true;
}

