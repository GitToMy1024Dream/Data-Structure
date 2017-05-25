#pragma once
#include <iostream>
#include <stack>
using namespace std;
enum PointIhfo 
{
	LINK, //0  表示指向左右孩子的指针
	THREAD //1  表示指向前驱或后继的线索
};
template<class T>
struct BinaryTreeNodeThd//线索二叉树
{
	T _data;
	BinaryTreeNodeThd<T>* _pLeft;//指向左孩子的指针
	BinaryTreeNodeThd<T>* _pRight;//指向右孩子的指针
	BinaryTreeNodeThd<T>* _pParent;//指向双亲的指针
	PointIhfo _leftThread;//左线索标志
	PointIhfo _rightTrhead;//右线索标志
 
	BinaryTreeNodeThd(const T& data)
		: _data(data)
		, _pLeft(NULL)
		, _pRight(NULL)
		, _leftThread(LINK)
		, _rightTrhead(LINK)
	{}
};
template<class T>
class BinaryTreeThd
{
	typedef BinaryTreeNodeThd<T> Node;
public:
	//空二叉树的构造函数
	BinaryTreeThd()
		: _pRoot(NULL)
	{}
	BinaryTreeThd(const T array[], size_t size, const T& invalid)
	{
		size_t index = 0;
		_CreateTree(_pRoot, array, size, index, invalid);//构建二叉树
	}
	//前序线索化
	void PreThread()
	{
		Node* prev = NULL;
		_PreThread(_pRoot, prev);
	}
	//中序线索化
	void InThread()
	{
		Node* prev = NULL;
		_InThread(_pRoot, prev);
	}
	//后序线索化
	void PostThread()
	{
		Node* prev = NULL;
		_PostThread(_pRoot, prev);
	}
	//前序线索化遍历
	void PreOrder()
	{
		_PreOrder(_pRoot);
	}
	//中序线索化遍历
	void InOrder()
	{
		_InOrder(_pRoot);
	}
	//后序线索化遍历
	void PostOrder()
	{
		_PostOrder(_pRoot);
	}
protected:
	void _PreOrder(Node* _root)
	{
		if (_root == NULL)
			return;
		Node* pCur = _root;
		while (pCur)
		{
			//左孩子存在且左线索为LINK，即找到最左边的孩子节点
			while (pCur->_pLeft && pCur->_leftThread == LINK)
			{
				cout << pCur->_data << " ";
				pCur = pCur->_pLeft;
			}
			//访问最左边的结点
			cout << pCur->_data << " ";
			//左孩子是线索时，遍历右孩子
			if (pCur->_leftThread == THREAD)
			{
				pCur = pCur->_pRight;
			}
			while (pCur)//遍历右结点
			{
				//左结点存在且做线索为LINK时，访问当前节点
				if (pCur->_pLeft && pCur->_leftThread == LINK)
					break;
				cout << pCur->_data << " ";
				pCur = pCur->_pRight;//继续遍历右孩子
			}
		}
		cout << endl;
	}
	void _InOrder(Node* _root)
	{
		if (_root == NULL)
			return;
		Node* pCur = _root;
		Node* prev = NULL;
		while (pCur)
		{
			//找到最左边的结点，不访问
			while (pCur->_pLeft && pCur->_leftThread == LINK)
			{
				pCur = pCur->_pLeft;
			}
			//访问当前节点即最左边的结点
			cout << pCur->_data << " ";
			//当前节点存在且右孩子是一个线索，寻找中序的后继结点
			while (pCur && pCur->_rightTrhead == THREAD)
			{
				pCur = pCur->_pRight;
				cout << pCur->_data << " ";
			}
			//存在右子树时，以新的子树遍历
			pCur = pCur->_pRight;
		}
		cout << endl;
	}
	void _PostOrder(Node* _root)
	{
		if (_root == NULL)
			return;
		Node* pCur = _root;
		Node* prev = NULL;
		while (pCur)
		{
			//当前节点的左子树没有访问
			if (prev != pCur->_pLeft)
			{
				//1.找到最左边的结点
				while (pCur->_leftThread == LINK)
				{
					pCur = pCur->_pLeft;
				}
				//访问连在一起的结点
				//注意：左单支
				while (pCur->_rightTrhead == THREAD)
				{
					cout << pCur->_data << " ";
					prev = pCur;
					pCur = pCur->_pRight;
				}
				//处理左丹志
				//第二个条件，约束右单支
				if (pCur == _root && _root->_pRight == NULL)
				{
					cout << pCur->_data << endl;
					return;
				}
				//处理右单支
				while (pCur && pCur->_pRight == prev)
				{
					cout << pCur->_data << " ";
					prev = pCur;
					pCur = pCur->_pParent;//往上一级走
				}
				if (pCur && pCur->_rightTrhead == LINK)
					pCur = pCur->_pRight;
			}
		}	
	}
private:
	//递归构建二叉树
	void _CreateTree(Node*& pRoot, const T array[], size_t size,
		size_t& index, const T& invalid)
	{
		if (index < size && invalid != array[index])
		{
			pRoot = new Node(array[index]);
			_CreateTree(pRoot->_pLeft, array, size, ++index, invalid);
			if (pRoot->_pLeft)
			{
				pRoot->_pLeft->_pParent = pRoot;
			}
			_CreateTree(pRoot->_pRight, array, size, ++index, invalid);
			if (pRoot->_pRight)
			{
				pRoot->_pRight->_pParent = pRoot;
			}
		}
	}
	// 前序线索化(用stack实现)
	void _PreThread(Node* pRoot, Node*& prev)
	{
		//空树
		if (pRoot == NULL)
			return;
		Node* pCur = pRoot;
		stack<Node*> _s;
		_s.push(pRoot);//将让根节点入栈
		while (pCur || !_s.empty())
		{
			Node* tmp = NULL;
			//栈不为空时
			if (!_s.empty())
			{
				tmp = _s.top();//保存栈顶元素
			}
			else
				return;//循环的最终终止条件，栈空
			_s.pop();
			//右孩子存在，入栈
			if (tmp->_pRight)
			{
				_s.push(tmp->_pRight);
			}
			//左孩子存在，入栈
			if (tmp->_pLeft)
			{
				_s.push(tmp->_pLeft);
			}
			//左孩子不存在
			else
			{
				tmp->_leftThread = THREAD;//将左孩子的线索标记为THREAD
				//当前节点指向前一个保存的结点,第一次进来prev是指向NULL的
				tmp->_pLeft = prev;
			}
			//上一个节点存在且没有右子树
			if (prev && prev->_pRight == NULL)
			{
				tmp->_rightTrhead = THREAD;//将当前节点的右孩子标记为线索
				prev->_pRight = tmp;//前一个节点的后继指向当前节点
			}
			prev = tmp;//前驱指针prev每次都保存上一次的节点
		}
	}
	// 中序线索化
	void _InThread(Node* pRoot, Node* &prev)
	{
		if (pRoot == NULL)
			return;
		Node* pCur = pRoot;
		stack<Node*> _s;
		while (!_s.empty() || pCur)
		{
			//找到最左边的结点
			while (pCur)
			{
				_s.push(pCur);
				pCur = pCur->_pLeft;
			}
			//保存栈顶元素，即最左边的结点
			pCur = _s.top();
			//左孩子不存在，标记其线索为THREAD，
			//并让当前节点的的左指针域(前驱)指向前一个节点
			if (pCur->_pLeft == NULL)
			{
				pCur->_leftThread = THREAD;
				//第一次进来是NULL，之后是当前节点的前一个节点
				pCur->_pLeft = prev;
			}
			_s.pop();
			prev = pCur;//更新保存当前节点的前一个节点
			//遍历右孩子，若右孩子不存在且栈不为空
			//将当前节点的右指针域标记为线索
			//并将右指针域指向栈顶元素，即后继结点
			if (pCur->_pRight == NULL && !_s.empty())
			{
				pCur->_rightTrhead = THREAD;
				pCur->_pRight = _s.top();
				pCur = NULL;
			}
			//右孩子存在时，把它当成一个子树进行遍历
			else
			{
				pCur = pCur->_pRight;
			}
		}
	}
	// 后续线索化
	void _PostThread(Node* pRoot, Node* &prev)
	{
		if (pRoot == NULL)
			return;
		stack<Node*> _s;
		Node* pCur = pRoot;
		while (pCur || !_s.empty())
		{
			//找到最左边的结点，保存经过的所有的结点
			while (pCur)
			{
				_s.push(pCur);
				pCur = pCur->_pLeft;
			}
			//保存当前的栈顶元素即最左边的结点
			Node* tmp = _s.top();
			//当前节点右子树不存在或者右子树访问过
			//prev为当前节点的前一个节点
			if (tmp->_pRight == NULL || tmp->_pRight == prev)
			{
				//左子树不存在时，左指针域标记为线索，
				//并指向当前节点的前一个节点
				if (tmp->_pLeft == NULL)
				{
					tmp->_leftThread = THREAD;
					//第一次进来prev为NULL
					tmp->_pLeft = prev;
				}
				//前一个节点存在且不存在右子树时
				//将前一个节点的右指针域标记为线索
				//并且后继指向当前节点
				if (prev && prev->_pRight == NULL)
				{
					tmp->_rightTrhead = THREAD;
					prev->_pRight = tmp;
				}
				_s.pop();
				prev = tmp;//更新保存前一个节点
			}
			//右子树存在，以新的子树看待进行遍历
			else
			{
				pCur = tmp->_pRight;
			}
		}
	}
protected:
	Node* _pRoot;
};