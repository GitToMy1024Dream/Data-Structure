#pragma once
#include <iostream>
using namespace std;
template<class K, size_t M>
struct BTreeNode
{
	// 多给一个关键字：为简化分裂的逻辑
	K _keys[M];     // 关键字的集合
	BTreeNode<K, M>* _pSub[M + 1];    // 孩子的集合
	BTreeNode<K, M>* _pParent;
	size_t _size; // 有效关键字的个数
	BTreeNode()
		: _size(0)
		, _pParent(NULL)
	{
		for (size_t idx = 0; idx < M + 1; ++idx)
			_pSub[idx] = NULL;
	}
};

template<class K, size_t M>
class BTree
{
	typedef BTreeNode<K, M> Node;
public:
	BTree()
		: _pRoot(NULL)
	{}
	~BTree()
	{
		_Destroy(_pRoot);
	}
	//查找值为key的结点
	pair<Node*, int> Find(const K& key)
	{
		Node* pCur = _pRoot;
		Node* pParent = NULL;
		while (pCur)
		{
			size_t idx = 0;
			//下标必须小于关键字key的个数	
			while (idx < pCur->_size)
			{
				//小于当前节点的值跳出循环指向孩子节点，大于在此节点内向右偏移，相等返回当前节点
				if (key < pCur->_keys[idx])
					break;
				else if (key > pCur->_keys[idx])
					++idx;
				else
					return pair<Node*, int>(pCur,idx);
			}
			pParent = pCur;
			pCur = pCur->_pSub[idx];
		}
		return pair<Node*, int>(pParent, -1);
	}
	//插入
	bool Insert(const K& key)
	{
		//空树
		if (_pRoot == NULL)
		{
			_pRoot = new Node;
			_pRoot->_keys[0] = key;
			_pRoot->_size = 1;
			_pRoot->_pParent = NULL;
			return true;
		}
		//寻找插入位置
		pair<Node*, int> pos = Find(key);
		//键值已经存在,直接退出
		if (pos.second != -1)
			return false;
		//插入
		Node* pCur = pos.first;
		Node* pSub = NULL;
		K k = key;
		while (1)
		{
			_InsertKey(pCur, k, pSub);//插入键值k
			if (pCur->_size < M)
				return true;
			//分裂节点
			size_t mid = pCur->_size >> 1;
			Node* NewNode = new Node;
			size_t i = mid + 1;
			size_t j = 0;
			for (; i < pCur->_size; ++i, ++j)
			{
				NewNode->_keys[j] = pCur->_keys[i];//复制关键字
				NewNode->_pSub[j] = pCur->_pSub[i];//复制孩子
				if (NewNode->_pSub[j])//孩子存在就指向新节点
					NewNode->_pSub[j]->_pParent = NewNode;
				NewNode->_size++;
			}
			//将最后一个右孩子也复制过来
			NewNode->_pSub[NewNode->_size] = pCur->_pSub[i];
			if (pCur->_pSub[i])
				pCur->_pSub[i]->_pParent = NewNode;
			pCur->_size = pCur->_size - NewNode->_size - 1;
			//如果分裂的结点为根节点
			if (pCur == _pRoot)
			{
				_pRoot = new Node;
				_pRoot->_keys[0] = pCur->_keys[mid];
				_pRoot->_size = 1;
				_pRoot->_pSub[0] = pCur;
				pCur->_pParent = _pRoot;
				_pRoot->_pSub[1] = NewNode;
				NewNode->_pParent = _pRoot;
				return true;
			}
			else
			{
				k = pCur->_keys[mid];
				pCur = pCur->_pParent;
				pSub = NewNode;
			}
		}
	}
	//中序遍历
	void InOrder()
	{
		cout << " InOrder:";
		_InOrder(_pRoot);
		cout << endl;
	}
private:
	//中序遍历
	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			for (size_t idx = 0; idx < pRoot->_size; ++idx)
			{
				_InOrder(pRoot->_pSub[idx]);
				cout << pRoot->_keys[idx] << " ";
			}
			_InOrder(pRoot->_pSub[pRoot->_size]);
		}
	}
	//插入key值
	void _InsertKey(Node* pCur, const K& key, Node* pSub)
	{
		int end = pCur->_size - 1;
		while (end >= 0)
		{
			if (key < pCur->_keys[end])
			{
				pCur->_keys[end + 1] = pCur->_keys[end];//向后移动
				pCur->_pSub[end + 2] = pCur->_pSub[end + 1];//键值移动时带上孩子
			}
			else
				break;
			--end;
		}
		pCur->_keys[end + 1] = key;
		pCur->_pSub[end + 2] = pSub;
		pCur->_size++;
		if (pSub)
		{
			pSub->_pParent = pCur;
		}
	}
	//销毁B树
	void _Destroy(Node* root)
	{
		if (root == NULL)
			return;
		for (size_t idx = 0; idx < root->_size; ++idx)
		{
			_Destroy(root->_pSub[idx]);
		}
		_Destroy(root->_pSub[root->_size]);
	}
private:
	Node* _pRoot;
};