#pragma once
#include <iostream>
using namespace std;
template<class K, size_t M>
struct BTreeNode
{
	// ���һ���ؼ��֣�Ϊ�򻯷��ѵ��߼�
	K _keys[M];     // �ؼ��ֵļ���
	BTreeNode<K, M>* _pSub[M + 1];    // ���ӵļ���
	BTreeNode<K, M>* _pParent;
	size_t _size; // ��Ч�ؼ��ֵĸ���
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
	//����ֵΪkey�Ľ��
	pair<Node*, int> Find(const K& key)
	{
		Node* pCur = _pRoot;
		Node* pParent = NULL;
		while (pCur)
		{
			size_t idx = 0;
			//�±����С�ڹؼ���key�ĸ���	
			while (idx < pCur->_size)
			{
				//С�ڵ�ǰ�ڵ��ֵ����ѭ��ָ���ӽڵ㣬�����ڴ˽ڵ�������ƫ�ƣ���ȷ��ص�ǰ�ڵ�
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
	//����
	bool Insert(const K& key)
	{
		//����
		if (_pRoot == NULL)
		{
			_pRoot = new Node;
			_pRoot->_keys[0] = key;
			_pRoot->_size = 1;
			_pRoot->_pParent = NULL;
			return true;
		}
		//Ѱ�Ҳ���λ��
		pair<Node*, int> pos = Find(key);
		//��ֵ�Ѿ�����,ֱ���˳�
		if (pos.second != -1)
			return false;
		//����
		Node* pCur = pos.first;
		Node* pSub = NULL;
		K k = key;
		while (1)
		{
			_InsertKey(pCur, k, pSub);//�����ֵk
			if (pCur->_size < M)
				return true;
			//���ѽڵ�
			size_t mid = pCur->_size >> 1;
			Node* NewNode = new Node;
			size_t i = mid + 1;
			size_t j = 0;
			for (; i < pCur->_size; ++i, ++j)
			{
				NewNode->_keys[j] = pCur->_keys[i];//���ƹؼ���
				NewNode->_pSub[j] = pCur->_pSub[i];//���ƺ���
				if (NewNode->_pSub[j])//���Ӵ��ھ�ָ���½ڵ�
					NewNode->_pSub[j]->_pParent = NewNode;
				NewNode->_size++;
			}
			//�����һ���Һ���Ҳ���ƹ���
			NewNode->_pSub[NewNode->_size] = pCur->_pSub[i];
			if (pCur->_pSub[i])
				pCur->_pSub[i]->_pParent = NewNode;
			pCur->_size = pCur->_size - NewNode->_size - 1;
			//������ѵĽ��Ϊ���ڵ�
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
	//�������
	void InOrder()
	{
		cout << " InOrder:";
		_InOrder(_pRoot);
		cout << endl;
	}
private:
	//�������
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
	//����keyֵ
	void _InsertKey(Node* pCur, const K& key, Node* pSub)
	{
		int end = pCur->_size - 1;
		while (end >= 0)
		{
			if (key < pCur->_keys[end])
			{
				pCur->_keys[end + 1] = pCur->_keys[end];//����ƶ�
				pCur->_pSub[end + 2] = pCur->_pSub[end + 1];//��ֵ�ƶ�ʱ���Ϻ���
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
	//����B��
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