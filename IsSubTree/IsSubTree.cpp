#include <iostream>
using namespace std;

struct Node
{
	int _value;
	Node* _left;
	Node* _right;
};

//子树的根相同时，判断左右子树是否相同
int IsSubTreeSameRoot(Node* pRoot1, Node* pRoot2)
{
	if (pRoot2 == NULL)
		return 1;
	if (pRoot1 == NULL)
		return -1;
	int i = IsSubTreeSameRoot(pRoot1->_left, pRoot1->_left);//递归左孩子
	int j = IsSubTreeSameRoot(pRoot1->_right, pRoot2->_right);//递归右孩子
	//左右子树都相同时才满足子树性质
	if (i && j)
		return 1;
	else
		return -1;
}

int IsSubTree(Node* pRoot1, Node* pRoot2)
{
	//空树是任何树的子树
	if (pRoot2 == NULL)
		return 1;
	if (pRoot1 == NULL)
		return -1;
	//根节点相同时，判断左右子树
	if (pRoot1->_value == pRoot2->_value)
		return IsSubTreeSameRoot(pRoot1, pRoot2);
	//根节点不相等时，看pRoo1的左子树中是否满足
	int flag = IsSubTree(pRoot1->_left, pRoot2);
	if (flag)
		return 1;
	//根节点不相等且左子树也不满足时，看pRoot2的右子树是否满足
	else
		return IsSubTree(pRoot2->_right, pRoot2);
}


int main()
{
	system("pause");
	return 0;
}