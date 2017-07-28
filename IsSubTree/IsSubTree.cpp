#include <iostream>
using namespace std;

struct Node
{
	int _value;
	Node* _left;
	Node* _right;
};

//�����ĸ���ͬʱ���ж����������Ƿ���ͬ
int IsSubTreeSameRoot(Node* pRoot1, Node* pRoot2)
{
	if (pRoot2 == NULL)
		return 1;
	if (pRoot1 == NULL)
		return -1;
	int i = IsSubTreeSameRoot(pRoot1->_left, pRoot1->_left);//�ݹ�����
	int j = IsSubTreeSameRoot(pRoot1->_right, pRoot2->_right);//�ݹ��Һ���
	//������������ͬʱ��������������
	if (i && j)
		return 1;
	else
		return -1;
}

int IsSubTree(Node* pRoot1, Node* pRoot2)
{
	//�������κ���������
	if (pRoot2 == NULL)
		return 1;
	if (pRoot1 == NULL)
		return -1;
	//���ڵ���ͬʱ���ж���������
	if (pRoot1->_value == pRoot2->_value)
		return IsSubTreeSameRoot(pRoot1, pRoot2);
	//���ڵ㲻���ʱ����pRoo1�����������Ƿ�����
	int flag = IsSubTree(pRoot1->_left, pRoot2);
	if (flag)
		return 1;
	//���ڵ㲻�����������Ҳ������ʱ����pRoot2���������Ƿ�����
	else
		return IsSubTree(pRoot2->_right, pRoot2);
}


int main()
{
	system("pause");
	return 0;
}