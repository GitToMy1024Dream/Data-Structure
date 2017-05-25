#pragma once
#include <iostream>
#include <stack>
using namespace std;
enum PointIhfo 
{
	LINK, //0  ��ʾָ�����Һ��ӵ�ָ��
	THREAD //1  ��ʾָ��ǰ�����̵�����
};
template<class T>
struct BinaryTreeNodeThd//����������
{
	T _data;
	BinaryTreeNodeThd<T>* _pLeft;//ָ�����ӵ�ָ��
	BinaryTreeNodeThd<T>* _pRight;//ָ���Һ��ӵ�ָ��
	BinaryTreeNodeThd<T>* _pParent;//ָ��˫�׵�ָ��
	PointIhfo _leftThread;//��������־
	PointIhfo _rightTrhead;//��������־
 
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
	//�ն������Ĺ��캯��
	BinaryTreeThd()
		: _pRoot(NULL)
	{}
	BinaryTreeThd(const T array[], size_t size, const T& invalid)
	{
		size_t index = 0;
		_CreateTree(_pRoot, array, size, index, invalid);//����������
	}
	//ǰ��������
	void PreThread()
	{
		Node* prev = NULL;
		_PreThread(_pRoot, prev);
	}
	//����������
	void InThread()
	{
		Node* prev = NULL;
		_InThread(_pRoot, prev);
	}
	//����������
	void PostThread()
	{
		Node* prev = NULL;
		_PostThread(_pRoot, prev);
	}
	//ǰ������������
	void PreOrder()
	{
		_PreOrder(_pRoot);
	}
	//��������������
	void InOrder()
	{
		_InOrder(_pRoot);
	}
	//��������������
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
			//���Ӵ�����������ΪLINK�����ҵ�����ߵĺ��ӽڵ�
			while (pCur->_pLeft && pCur->_leftThread == LINK)
			{
				cout << pCur->_data << " ";
				pCur = pCur->_pLeft;
			}
			//��������ߵĽ��
			cout << pCur->_data << " ";
			//����������ʱ�������Һ���
			if (pCur->_leftThread == THREAD)
			{
				pCur = pCur->_pRight;
			}
			while (pCur)//�����ҽ��
			{
				//���������������ΪLINKʱ�����ʵ�ǰ�ڵ�
				if (pCur->_pLeft && pCur->_leftThread == LINK)
					break;
				cout << pCur->_data << " ";
				pCur = pCur->_pRight;//���������Һ���
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
			//�ҵ�����ߵĽ�㣬������
			while (pCur->_pLeft && pCur->_leftThread == LINK)
			{
				pCur = pCur->_pLeft;
			}
			//���ʵ�ǰ�ڵ㼴����ߵĽ��
			cout << pCur->_data << " ";
			//��ǰ�ڵ�������Һ�����һ��������Ѱ������ĺ�̽��
			while (pCur && pCur->_rightTrhead == THREAD)
			{
				pCur = pCur->_pRight;
				cout << pCur->_data << " ";
			}
			//����������ʱ�����µ���������
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
			//��ǰ�ڵ��������û�з���
			if (prev != pCur->_pLeft)
			{
				//1.�ҵ�����ߵĽ��
				while (pCur->_leftThread == LINK)
				{
					pCur = pCur->_pLeft;
				}
				//��������һ��Ľ��
				//ע�⣺��֧
				while (pCur->_rightTrhead == THREAD)
				{
					cout << pCur->_data << " ";
					prev = pCur;
					pCur = pCur->_pRight;
				}
				//������־
				//�ڶ���������Լ���ҵ�֧
				if (pCur == _root && _root->_pRight == NULL)
				{
					cout << pCur->_data << endl;
					return;
				}
				//�����ҵ�֧
				while (pCur && pCur->_pRight == prev)
				{
					cout << pCur->_data << " ";
					prev = pCur;
					pCur = pCur->_pParent;//����һ����
				}
				if (pCur && pCur->_rightTrhead == LINK)
					pCur = pCur->_pRight;
			}
		}	
	}
private:
	//�ݹ鹹��������
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
	// ǰ��������(��stackʵ��)
	void _PreThread(Node* pRoot, Node*& prev)
	{
		//����
		if (pRoot == NULL)
			return;
		Node* pCur = pRoot;
		stack<Node*> _s;
		_s.push(pRoot);//���ø��ڵ���ջ
		while (pCur || !_s.empty())
		{
			Node* tmp = NULL;
			//ջ��Ϊ��ʱ
			if (!_s.empty())
			{
				tmp = _s.top();//����ջ��Ԫ��
			}
			else
				return;//ѭ����������ֹ������ջ��
			_s.pop();
			//�Һ��Ӵ��ڣ���ջ
			if (tmp->_pRight)
			{
				_s.push(tmp->_pRight);
			}
			//���Ӵ��ڣ���ջ
			if (tmp->_pLeft)
			{
				_s.push(tmp->_pLeft);
			}
			//���Ӳ�����
			else
			{
				tmp->_leftThread = THREAD;//�����ӵ��������ΪTHREAD
				//��ǰ�ڵ�ָ��ǰһ������Ľ��,��һ�ν���prev��ָ��NULL��
				tmp->_pLeft = prev;
			}
			//��һ���ڵ������û��������
			if (prev && prev->_pRight == NULL)
			{
				tmp->_rightTrhead = THREAD;//����ǰ�ڵ���Һ��ӱ��Ϊ����
				prev->_pRight = tmp;//ǰһ���ڵ�ĺ��ָ��ǰ�ڵ�
			}
			prev = tmp;//ǰ��ָ��prevÿ�ζ�������һ�εĽڵ�
		}
	}
	// ����������
	void _InThread(Node* pRoot, Node* &prev)
	{
		if (pRoot == NULL)
			return;
		Node* pCur = pRoot;
		stack<Node*> _s;
		while (!_s.empty() || pCur)
		{
			//�ҵ�����ߵĽ��
			while (pCur)
			{
				_s.push(pCur);
				pCur = pCur->_pLeft;
			}
			//����ջ��Ԫ�أ�������ߵĽ��
			pCur = _s.top();
			//���Ӳ����ڣ����������ΪTHREAD��
			//���õ�ǰ�ڵ�ĵ���ָ����(ǰ��)ָ��ǰһ���ڵ�
			if (pCur->_pLeft == NULL)
			{
				pCur->_leftThread = THREAD;
				//��һ�ν�����NULL��֮���ǵ�ǰ�ڵ��ǰһ���ڵ�
				pCur->_pLeft = prev;
			}
			_s.pop();
			prev = pCur;//���±��浱ǰ�ڵ��ǰһ���ڵ�
			//�����Һ��ӣ����Һ��Ӳ�������ջ��Ϊ��
			//����ǰ�ڵ����ָ������Ϊ����
			//������ָ����ָ��ջ��Ԫ�أ�����̽��
			if (pCur->_pRight == NULL && !_s.empty())
			{
				pCur->_rightTrhead = THREAD;
				pCur->_pRight = _s.top();
				pCur = NULL;
			}
			//�Һ��Ӵ���ʱ����������һ���������б���
			else
			{
				pCur = pCur->_pRight;
			}
		}
	}
	// ����������
	void _PostThread(Node* pRoot, Node* &prev)
	{
		if (pRoot == NULL)
			return;
		stack<Node*> _s;
		Node* pCur = pRoot;
		while (pCur || !_s.empty())
		{
			//�ҵ�����ߵĽ�㣬���澭�������еĽ��
			while (pCur)
			{
				_s.push(pCur);
				pCur = pCur->_pLeft;
			}
			//���浱ǰ��ջ��Ԫ�ؼ�����ߵĽ��
			Node* tmp = _s.top();
			//��ǰ�ڵ������������ڻ������������ʹ�
			//prevΪ��ǰ�ڵ��ǰһ���ڵ�
			if (tmp->_pRight == NULL || tmp->_pRight == prev)
			{
				//������������ʱ����ָ������Ϊ������
				//��ָ��ǰ�ڵ��ǰһ���ڵ�
				if (tmp->_pLeft == NULL)
				{
					tmp->_leftThread = THREAD;
					//��һ�ν���prevΪNULL
					tmp->_pLeft = prev;
				}
				//ǰһ���ڵ�����Ҳ�����������ʱ
				//��ǰһ���ڵ����ָ������Ϊ����
				//���Һ��ָ��ǰ�ڵ�
				if (prev && prev->_pRight == NULL)
				{
					tmp->_rightTrhead = THREAD;
					prev->_pRight = tmp;
				}
				_s.pop();
				prev = tmp;//���±���ǰһ���ڵ�
			}
			//���������ڣ����µ������������б���
			else
			{
				pCur = tmp->_pRight;
			}
		}
	}
protected:
	Node* _pRoot;
};