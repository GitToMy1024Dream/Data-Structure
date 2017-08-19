#include "list.h"


void test()
{
	Node* node1 = new Node(1);
	Node* node2 = new Node(2);
	Node* node3 = new Node(3);
	Node* node4 = new Node(4);
	Node* node5 = new Node(5);
	node1->_pnext = node2;
	node2->_pnext = node3;
	node3->_pnext = node4;
	node4->_pnext = node5;
	node5->_pnext = node3;
	Node* _node1 = new Node(10);
	Node* _node2 = new Node(20);
	Node* _node3 = new Node(30);
	_node1->_pnext = _node2;
	_node2->_pnext = _node3;
	_node3->_pnext = NULL;
	//cout << HasCicle(node1) << endl;
	//cout << GetCircleLength(node1) << endl;
	//cout << EntryCicle(node1)->_data << endl;
	//cout << IsIntersected(node1, _node1) << endl;
	//cout << GetFirstCommonNode(node1, _node1)->_data << endl;
	cout<< IsIntersectedCicle(node1,_node1)<<endl;
}

int main()
{
	test();
	system("pause");
	return 0;
}