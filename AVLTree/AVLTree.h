#pragma once
#include <iostream>
#include <cstdlib>
#include <assert.h>
using namespace std;
#pragma warning (disable:4996)
template<class K, class V>
struct AVLTreeNode//AVL���Ľṹ
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
	int _bf;       // ƽ�����ӣ�right-left
};
 
template<class K, class V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	//���캯��
	AVLTree()
		: _pRoot(NULL)
	{}
	//��������
	~AVLTree()
	{
		DestroyTree(_pRoot);
	}
	//����
	bool Insert(const K& key, const V& value)
	{
		if (_pRoot == NULL)//����
		{
			_pRoot = new Node(key, value);
			return true;
		}
		Node* pCur = _pRoot;
		Node* pParent = NULL;
		//Ѱ�Ҳ���λ��
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
		//�жϲ���λ���ǵ�ǰ˫�׵����ӻ��Һ���
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
		//����ƽ������
		while (pParent)
		{
			if (pParent->_pLeft == pCur)
				pParent->_bf--;
			else
				pParent->_bf++;
			//pParent�����ӻ��Һ���
			if (pParent->_bf == 0)
				return true;
			//pParent��Ҷ�ӽ��
			else if (pParent->_bf == 1 || pParent->_bf == -1)
			{
				pCur = pParent;
				pParent = pParent->_pParent;
			}
			//4���������
			else if (pParent->_bf == -2 || pParent->_bf == 2)
			{
				if (pParent->_bf == 2)
				{
					if (pCur->_bf == 1)//ͬ��
					{
						_RotateL(pParent);//����
						return true;
					}
					else//���
					{
						_RotateRL(pParent);//����˫��
						return true;
					}
				}
				else if (pParent->_bf == -2)
				{
					if (pCur->_bf == 1)//���
					{
						_RotateLR(pParent);//����˫��
						return true;
					}
					else//ͬ��
					{
						_RotateR(pParent);//����
						return true;
					}
				}
			}
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
	//��ȡ���ĸ߶�
	size_t Height()
	{
		return _Height(_pRoot);
	}
	//�ж϶������Ƿ�ƽ��
	bool IsBalanceTree()
	{
		return _IsBalanceTree(_pRoot);
	}
	//����
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
	//�ж��Ƿ�ƽ��
	bool _IsBalanceTree(Node* pRoot)
	{
		if (pRoot == NULL)
			return false;
		size_t height = abs((long)(_Height(pRoot->_pRight) - _Height(pRoot->_pLeft)));
		return (height < 2) && (_IsBalanceTree(pRoot->_pLeft)) && (_IsBalanceTree(pRoot->_pRight));
	}
	//���ĸ߶�
	size_t _Height(Node* pRoot)
	{
		if (pRoot == NULL)
			return 0;
		size_t leftHeight = _Height(pRoot->_pLeft) + 1;
		size_t rightHeight = _Height(pRoot->_pRight) + 1;
		return leftHeight > rightHeight ? leftHeight : rightHeight;
	}
	//����ݹ��ӡ(�����stack)
	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_key << " ";
			_InOrder(pRoot->_pRight);
		}
	}
	//����
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
		//���ڵ��˫���Ƿ����
		if (ppParent == NULL)
		{
			_pRoot = pSubR;
			pSubR->_pParent = NULL;
		}
		//���ڵ��˫�״���
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
		pParent->_bf = pSubR->_bf = 0;//��ƽ��������0
	}
	//�ҵ���
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
		//���ڵ��˫���Ƿ����
		if (ppParent == NULL)
		{
			_pRoot = pSubL;
			pSubL->_pParent = NULL;//��ƽ��������0
		}
		//���ڵ��˫�״���
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
	//����˫��
	void _RotateLR(Node* pParent)
	{
		assert(pParent);
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		int bf = pSubLR->_bf;
		_RotateL(pSubL);
		_RotateR(pParent);
		//bf = 0����pSubLRΪ����Ľ��
		if (bf == 0)
		{
			pSubL->_bf = pParent->_bf = 0;
		}
		//bf = 1��֤���������pSubLR���Һ���
		if (bf == 1)
		{
			pSubL->_bf = -1;
			pParent->_bf = 0;
		}
		//bf = -1��֤���������pSubLR������
		else
		{
			pSubL->_bf = 0;
			pParent->_bf = 1;
		}
		pSubLR->_bf = 0;
	}
	//����˫��
	void _RotateRL(Node* pParent)
	{
		assert(pParent);
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		int bf = pSubRL->_bf;
		_RotateR(pSubR);
		_RotateL(pParent);
		//bf = 0��֤������Ľ��ΪpSubRL
		if (bf == 0)
		{
			pParent->_bf = pSubR->_bf = 0;
		}
		//bf = 1������Ľ��ΪpSubRL���Һ���
		if (bf == 1)
		{
			pSubR->_bf = 0;
			pParent->_bf = -1;
		}
		//bf = -1,����Ľ��ΪpSubRL������
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