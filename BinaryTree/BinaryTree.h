#pragma once
#include <iostream>
#include <assert.h>
#include <queue>
#include <stack>
using namespace std;
template<class T>
struct BinaryTreeNode//����ڵ�
{
	T m_nValue;//��ǰ�ڵ��ֵ
	BinaryTreeNode<T>* m_pLeft;//ָ�����ӵ�ָ��
	BinaryTreeNode<T>* m_pRight;//ָ���Һ��ӵ�ָ��
	BinaryTreeNode(const T& data)
		:m_nValue(data)
		, m_pLeft(NULL)
		, m_pRight(NULL)
	{}
};
template<class T>
class BinaryTree//�������Ļ�������
{
	
public:
	typedef BinaryTreeNode<T> Node;
	//���������Ĺ��캯��
	BinaryTree();
	//��4�������Ĺ��캯��
	BinaryTree(T *arr, size_t size, const T& invalid);
	//�������캯��
	BinaryTree(BinaryTree<T>& _b);
	//��ֵ�����������
	BinaryTree<T>& operator=(BinaryTree<T>& s);
	//��������
	~BinaryTree();
	//����������
	Node* CreateTree(T* arr, size_t size, const T& invalid, size_t& index)
	{
		Node* pRoot = NULL;
		if (index < size)
		{
			//��������������������
			if (arr[index] != invalid)
			{
				pRoot = new Node(arr[index]);
				pRoot->m_pLeft = CreateTree(arr, size, invalid, ++index);
				pRoot->m_pRight = CreateTree(arr, size, invalid, ++index);
			}
		}
		return pRoot;
	}
	//����������
	Node* Copy(Node* pRoot)
	{
		Node* pCur = pRoot;
		if (pCur)
		{
			//���ȿ������ڵ�
			//�ڿ���������
			//�ۿ���������
			pCur = new Node(pRoot->m_nValue);
			pCur->m_pLeft = Copy(pRoot->m_pLeft);
			pCur->m_pRight = Copy(pRoot->m_pRight);
		}
		return pCur;
	}
	//�ͷŶ������Ľ��
	Node* Destroy(Node* pRoot)
	{
		if (pRoot)
		{
			//�����ͷ�������
			//�����ͷ�������
			//������ͷŸ��ڵ�
			pRoot->m_pLeft = Destroy(pRoot->m_pLeft);
			pRoot->m_pRight = Destroy(pRoot->m_pRight);
			delete pRoot;
			pRoot = NULL;
		}
		return pRoot;
	}
	//ǰ������ݹ�
	void _PreOrder(Node* pRoot);
	//ǰ������ǵݹ�
	void _PreOrder_Nor(Node* pRoot);
	//�������
	void _InOrder(Node* pRoot);
	//��������ǵݹ�(ջ)
	void _InOrder_Nor(Node* pRoot);
	//�������
	void _PostOrder(Node* pRoot);
	//��������ǵݹ�(ջ)
	void _PostOrder_Nor(Node* pRoot);
	//�������(����)
	void _LevelOrder(Node* pRoot);
	void PreOrder();
	void InOrder();
	void PostOrder();
	void LevelOrder();
	//�������н��ĸ���
	size_t Size();
	size_t _Size(Node* pRoot);
	//�����������
	size_t Depth();
	size_t _Depth(Node* pRoot);
	//����ֵΪdata�Ľ��
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
			cout << "Ѱ�ҳɹ�:";
			return pRoot;
		}
		//�ݹ�������Ѱ��data
		Node* pTmp = _Find(pRoot->m_pLeft, data);
		//��������������
		if (pTmp == NULL)
		{
			//���������б���Ѱ��
			pTmp = _Find(pRoot->m_pRight, data);
		}
		return pTmp;
	}
	//����Node��������
	Node* GetLeftChild(Node* pCur)
	{
		return (pCur == NULL) ? NULL : pCur->m_pLeft;
	}
	//����Node�����Һ���
	Node* GetRightChild(Node* pCur)
	{
		return (pCur == NULL) ? NULL : pCur->m_pRight;
	}
	//����Node����˫�׽��
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
	//��ȡ��K����ĸ���
	size_t GetKLevelCount(size_t K);
	size_t _GetKLevelCount(Node* pRoot, size_t K);
	//��ȡҶ�ӽ��ĸ���
	size_t GetLeefCount();
	size_t _GetLeefCount(Node* pRoot);
	//�������ľ���
	void BinaryMirror();
	void _BinaryMirror(Node* pRoot);
	//�ж�һ���������Ƿ�Ϊ��ȫ������
	bool IsCompleteTree();
	bool _IsCompleteTree(Node* pRoot);
	//Ѱ�����ڵ�������������
	Node* FindRecentParent(Node* data1, Node* data2)
	{
		return _FindRecentParent(_root,data1,data2);
	}
	//��ȡNode����·��
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

//ǰ������ݹ�
template<class T>
void BinaryTree<T>::_PreOrder(Node* pRoot)
{
	if (pRoot)
	{
		cout << pRoot->m_nValue << " ";//�ȷ��ʵ�ǰ�ڵ�
		_PreOrder(pRoot->m_pLeft);//�ݹ鵱ǰ�ڵ��������
		_PreOrder(pRoot->m_pRight);//�ݹ鵱ǰ�ڵ��������
	}
}

//ǰ������ǵݹ�(ʹ��ջ)
template<class T>
void BinaryTree<T>::_PreOrder_Nor(Node* pRoot)
{
	//ǰ�᣺ջ��Ϊ��
	//��root��ջ
	//�ڱ���ջ��Ԫ��
	//�۳�ջ
	//�ܷ����������������ڣ���ջ
	//�ݷ����������������ڣ���ջ
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

//��������ݹ�
template<class T>
void BinaryTree<T>::_InOrder(Node* pRoot)
{
	if (pRoot)
	{
		_InOrder(pRoot->m_pLeft);//�ȵݹ�������
		cout << pRoot->m_nValue << " ";//�ڷ��ʵ�ǰ�ڵ�
		_InOrder(pRoot->m_pRight);//���ݹ�������
	}
}


//��������ǵݹ�(ʹ��ջ)
template<class T>
void BinaryTree<T>::_InOrder_Nor(Node* pRoot)
{
	Node* pCur = pRoot;
	stack<Node*> _s;
	//ջ��Ϊ�ջ��ߵ�ǰ�ڵ㲻Ϊ�գ�����δ������
	while (!_s.empty() || pCur)
	{
		//��������ڵ�(ֱ������ڵ�)ȫ��ѹ��ջ��
		while (pCur)
		{
			_s.push(pCur);
			pCur = pCur->m_pLeft;
		}
		Node* _Top = _s.top();//���浱ǰջ��Ԫ��
		cout << _Top->m_nValue << " ";//����ջ��Ԫ�ؼ����ڵ�
		_s.pop();//�����ڵ��ջ
		pCur = _Top->m_pRight;//��������ķ���ȥ����������
	}
}

//��������ݹ�
template<class T>
void BinaryTree<T>::_PostOrder(Node* pRoot)
{
	if (pRoot)
	{
		_PostOrder(pRoot->m_pLeft);//�ȵݹ�������
		_PostOrder(pRoot->m_pRight);//�ٵݹ�������
		cout << pRoot->m_nValue << " ";//�����ʵ�ǰ�ڵ�
	}
}
//��������ǵݹ�(ʹ��ջ)
template<class T>
void BinaryTree<T>::_PostOrder_Nor(Node* pRoot)
{
	if (pRoot == NULL)
		return;
	stack<Node*> _s;
	Node* pCur = pRoot;
	Node* pMark = NULL;//����Ƿ���ʹ��˽ڵ��ָ��
	//ջ��Ϊ�ջ��ߵ�ǰ�ڵ㲻Ϊ�գ�����δ������
	while (!_s.empty() || pCur)
	{
		//��������ڵ�(ֱ������ڵ�)ȫ��ѹ��ջ��
		while (pCur)
		{
			_s.push(pCur);
			pCur = pCur->m_pLeft;
		}
		Node* _Top = _s.top();//ȡջ��Ԫ��
		//���ջ��Ԫ��(���ڵ�)��������Ϊ�ջ����Ѿ����ʹ�
		if (_Top->m_pRight == NULL || _Top->m_pRight == pMark)
		{
			cout << _Top->m_nValue << " ";
			pMark = _Top;//��Mark��Ǵ˽ڵ��Ѿ�������
			_s.pop();
		}
		else//δ����������(������������)
		{
			pCur = _Top->m_pRight;//��������������
		}
	}
}

//�������(ʹ�ö���)
template<class T>
void BinaryTree<T>::_LevelOrder(Node* pRoot)
{
	queue<Node*> _q;
	if (pRoot)
		_q.push(pRoot);//���ڵ���ջ
	while (!_q.empty())//ջ��Ϊ��
	{
		Node* front = _q.front();//�����ͷԪ��
		cout << front->m_nValue << " ";
		_q.pop();//������
		if (front->m_pLeft)//���Ӵ��������
			_q.push(front->m_pLeft);
		if (front->m_pRight)//�Һ��Ӵ��������
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

//�������н��ĸ���
template<class T>
size_t BinaryTree<T>::Size()
{
	return _Size(_root);
}
template<class T>
size_t BinaryTree<T>::_Size(Node* pRoot)
{
	if (pRoot == NULL)//��Ϊ��
		return 0;
	else//����Ϊ��ʱ���ڵ����Ϊ���ڵ�+�������ڵ�+�Һ��ӽڵ�
		return 1 + _Size(pRoot->m_pLeft) + _Size(pRoot->m_pRight);
}


//�������
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
	//����Ϊ��ʱ,�����������ĸ߶�left���������ĸ߶�right
	size_t left = 1;
	size_t right = 1;
	left += _Depth(pRoot->m_pLeft);//����������+1��������+0
	right += _Depth(pRoot->m_pRight);//����������+1��������+0
	return left > right ? left : right;//���ض��ߵĽϴ���
}

//���ֵ�K��ڵ�ĸ���
template<class T>
size_t BinaryTree<T>::GetKLevelCount(size_t K)
{
	return _GetKLevelCount(_root, K);
}
template<class T>
size_t BinaryTree<T>::_GetKLevelCount(Node* pRoot, size_t K)
{
	
	if (pRoot == NULL || K < 1)//�Ƿ����
		return 0;
	if (K == 1)//���ڵ�Ϊ��1��
		return 1;
	//����ת���ɵ�K-1��������������ĸ���
	return _GetKLevelCount(pRoot->m_pLeft, K - 1) + _GetKLevelCount(pRoot->m_pRight, K - 1);
}

//����Ҷ�ӽ��ĸ���
template<class T>
size_t BinaryTree<T>::GetLeefCount()
{
	return _GetLeefCount(_root);
}
template<class T>
size_t BinaryTree<T>::_GetLeefCount(Node* pRoot)
{
	if (pRoot == NULL)//����
		return 0;
	if (pRoot->m_pLeft == NULL && pRoot->m_pRight == NULL)//ֻ�и��ڵ�
		return 1;
	//�ݹ������������Ҷ�ӽ��+��������Ҷ�ӽ��
	return _GetLeefCount(pRoot->m_pLeft) + _GetLeefCount(pRoot->m_pRight);
}


//�������ľ���(������������λ��)
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
	std::swap(pRoot->m_pLeft, pRoot->m_pRight);//������ǰ���������Ľ��
	_BinaryMirror(pRoot->m_pLeft);//������һ��������
	_BinaryMirror(pRoot->m_pRight);//������һ��������
}

//�ж϶������Ƿ�Ϊ��ȫ������
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

