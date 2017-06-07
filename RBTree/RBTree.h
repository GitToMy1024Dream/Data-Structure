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
	//���캯��
	RBTree()
		:_pRoot(NULL)
	{}
	//��������
	~RBTree()
	{
		_pRoot = _Destory(_pRoot);
	}
	//�������캯��
	RBTree(const RBTree<K, V>& rb)
	{
		if (it != &rb)
		{
			_pRoot = _Copy(_pRoot);
		}
	}
	//��ֵ�����������
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
	//����
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
		//δ���������ڵ��Ҹ��ڵ㻹�Ǻ�ɫ
		while (pCur != _pRoot && pParent->_color == RED)
		{
			Node* ppParent = pParent->_pParent;
			//�ȴ������
			if (ppParent->_pLeft == pParent)
			{
				Node* uncle = pParent->_pRight;
				//1.���������Ϊ��ɫ
				if (uncle && uncle->_color == RED)
				{
					pParent->_color = uncle->_color = BLACK;
					ppParent->_color = RED;
					pCur = ppParent;
					pParent = pCur->_pParent;
				}
				//2.���岻���ڻ�������Ϊ��ɫ
				else
				{
					//3.pCurΪpParent���Һ���
					if (pParent->_pRight == pCur)
					{
						_RotaeL(pParent);
						std::swap(pCur,pParent);
					}
					//2.pCurΪpParent������
					else
					{
						_RotaeR(ppParent);
						ppParent->_color = RED;
						pParent->_color = BLACK;
					}
				}
			}
			//�ٴ����ұߵ����(����������պ�λ���෴)
			else
			{
				Node* uncle = ppParent->_pLeft;
				//4.���������Ϊ��
				if (uncle && uncle->_color == RED)
				{
					pParent->_color = uncle->_color = BLACK;
					pCur->_color = RED;
					pCur = ppParent;
					pParent = pCur->_pParent;
				}
				//5.���岻���ڻ�������Ϊ��ɫ
				else
				{
					//6.pCurΪpParent������
					if (pParent->_pLeft == pCur)
					{
						_RotaeR(pParent);
						std::swap(pCur, ppParent);
					}
					//5.pCurΪpParent���Һ���
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
	//�ж��Ƿ�Ϊ�����
	bool CheckRBTree()
	{
		//�����϶��Ǻ����
		if (_pRoot == NULL)
			return true;
		//����1�����ڵ�Ϊ���Ȼ���Ǻ����
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
	//����
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
	//�������
	void InOrder()
	{
		_InOrder(_pRoot);
		cout << endl;
	}
protected:
	//�ж��Ƿ�����
	bool _CheckRBTree(Node* pRoot, const size_t& count, size_t K)
	{
		if (pRoot == NULL)
			return true;
		//����2���������ڵĽ�㶼Ϊ��ɫ
		if (pRoot->_pParent && pRoot->_color == pRoot->_pParent->_color == RED)
			return false;
		//����3���Ӹ��ڵ㵽Ҷ�ӽ���ÿ��·���ϵĺ�ɫ�ڵ�һ��
		if (pRoot->_color == BLACK)
			K++;
		//����Ҷ�ӽ����бȽ�
		if (pRoot->_pLeft == NULL && pRoot->_pRight == NULL)
		{
			if (count == K)
				return true;
			else
				return false;
		}
		return _CheckRBTree(pRoot->_pLeft, count, K) && _CheckRBTree(pRoot->_pRight, count, K);
	}
	//����
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
	//����
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
	//����
	void _RotaeL(Node* pParent)
	{
		assert(pParent);
		//�ϸ����������Ҳ����
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
		//ppParent������
		if (ppParent == NULL)
		{
			_pRoot = pSubR;
			pSubR->_pParent = NULL;
		}
		//ppParent����
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
	//����
	void _RotaeR(Node* pParent)
	{
		assert(pParent);
		//�ϸ���������������
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
			pSubL->_pParent = NULL;
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
private:
	Node* _pRoot;
};
