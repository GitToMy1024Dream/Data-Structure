#include <iostream>
using namespace std;

struct Node
{
	int _value;
	Node* _pnext;
	Node(const int& data)
		:_value(data)
		,_pnext(NULL)
	{}
};

void diffence(Node** LA, Node* LB)
{
	Node* pa = *LA;
	Node* pb = NULL;
	Node* prev = NULL;
	Node* del = NULL;
	while (pa)
	{
		pb = LB;
		//pb存在且pb与pa不等,在pb中寻找与pa相同的结点
		while (pb && pb->_value != pa->_value)
		{
			pb = pb->_pnext;
		}
		//pb存在，说明pa与pb肯定相等
		if (pb)
		{
			//prev为NULL说明第一次进来
			if (!prev)
				*LA = pa->_pnext;
			else
			{
				prev->_pnext = pa->_pnext;
			}
			//删除pa中重复的结点
			del = pa;
			pa = pa->_pnext;
			free(del);
		}
		//pb不存在，pa继续向后遍历
		else
		{
			prev = pa;
			pa = pa->_pnext;
		}

	}
}

void Create()
{
	Node* node1 = new Node(5);
	Node* node2 = new Node(10);
	Node* node3 = new Node(20);
	Node* node4 = new Node(15);
	Node* node5 = new Node(25);
	Node* node6 = new Node(30);
	Node* node7 = new Node(5);
	Node* node8 = new Node(15);
	Node* node9 = new Node(25);
	Node* node10 = new Node(35);
	
	node1->_pnext = node2;
	node2->_pnext = node3;
	node3->_pnext = node4;
	node4->_pnext = node5;
	node5->_pnext = node6;
	node6->_pnext = NULL;

	node7->_pnext = node8;
	node8->_pnext = node9;
	node9->_pnext = node10;
	node10->_pnext = NULL;

	diffence(&node1, node7);
}


int main()
{
	Create();
	system("pause");
	return 0;
}