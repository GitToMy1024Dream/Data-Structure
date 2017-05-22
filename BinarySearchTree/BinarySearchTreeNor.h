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

// �ǵݹ�汾
template<class K, class V>
class BinarySearchTree
{
	typedef BinarySearchTreeNode<K, V> Node;
public:
	BinarySearchTree()
		: _pRoot(NULL)
	{}
	//�������캯��
	BinarySearchTree(const BinarySearchTree& bst)
	{
		assert(bst._pRoot);
		_pRoot = Copy(bst._pRoot);
	}
	//��ֵ�����������
	BinarySearchTree<K, V>& operator=(const BinarySearchTree<K, V>& bst)
	{
		if (this != &bst)
		{
			BinarySearchTree<K, V> tmp(bst);
			std::swap(tmp._pRoot, _pRoot);
		}
		return *this;
	}
	//��������
	~BinarySearchTree()
	{
		if (_pRoot)
			Destroy(_pRoot);//����
	}
	//����ֵΪkey�Ľ��
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
	//����
	bool Insert(const K& key, const V& value)
	{
		if (_pRoot == NULL)
		{
			_pRoot = new Node(key,value);
			return true;
		}
		Node* pCur = _pRoot;
		Node* Parent = NULL;
		//Ѱ�Ҳ���λ��
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
		//�жϲ���Ľ����˫�׽������ӻ����Һ���
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
	//ɾ��
	bool Remove(const K& key)
	{
		if (_pRoot == NULL)//����
			return false;
		if (_pRoot->_pLeft == NULL && _pRoot->_pRight == NULL
			&& _pRoot->_key == key)//ֻ�и��ڵ�
			return true;
		Node* pCur = _pRoot;
		Node* pParent = NULL;
		//Ѱ��ɾ���ڵ��λ��
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
		//��Ϊ��
		if (pCur->_pLeft == NULL)
		{
			//���ɾ�����Ǹ��ڵ�
			if (pParent == NULL)
			{
				_pRoot = pCur->_pRight;
			}
			//ͼ2��ʾ���
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
		//��Ϊ�գ���Ϊ��
		else if (pCur->_pRight == NULL)
		{
			//ɾ�����ڵ�
			if (pParent == NULL)
			{
				_pRoot = pCur->_pLeft;
			}
			//ͼ3��ʾ���
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
		//���Ҷ���Ϊ��
		else
		{
			pParent = pCur;
			Node* MinNodeFromRight = pCur->_pRight;
			//Ѱ����������������ĵ�һ���ڵ�
			while (MinNodeFromRight->_pLeft)
			{
				pParent = MinNodeFromRight;
				MinNodeFromRight = MinNodeFromRight->_pLeft;
			}
			//����������ĵ�һ���ڵ����Ϣ��ֵ��˫��pCur
			pCur->_key = MinNodeFromRight->_key;
			pCur->_value = MinNodeFromRight->_value;
			//ͼ4��ʾ���
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
	//�������
	void InOrder()
	{
		cout << "InOrder: ";
		_InOrder(_pRoot);
		cout << endl;
	}
	//��ȡ��С���
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
	//��ȡ�����
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
	Node* Copy(Node* pRoot)//ǰ���������
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
	//�������ٶ�����
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
	//�������
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
