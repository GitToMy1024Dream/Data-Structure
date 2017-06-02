struct BinarySearchTreeNode
{
	int _value;
	BinarySearchTreeNode* _pLeft;
	BinarySearchTreeNode* _pRight;
}*Node;
template<class T>
class TreeToList
{
	typedef BinarySearchTreeNode Node;
public:
	TreeToList()
		:_pRoot(NULL)
	{}
	Node*& Transfrom(const Node* _pRoot)//_pRoot为树的根节点
	{
		Node* _prev = NULL;//记录链表的前一个节点
		_Transfrom(_pRoot,_prev);//BST->LIST
		while (_pRoot->_pLeft)//树的左边的结点即链表的头
			_pRoot = _pRoot->_pLeft;
		return _pRoot;
	}
protected:
	void _Transfrom(const Node* root, Node* _prev)
	{
		//空树
		if (root == NULL)
			return NULL;
		Node* pCur = root;
		_Transfrom(pCur->_pLeft, _prev);//递归左子树
		if (_prev)
		{
			_prev->_pRight = pCur;
		}
		pCur->_pLeft = _prev;
		_prev = pCur;
		_Transfrom(pCur->_pRight, _prev);//以子问题递归右子树
	}
private:
	Node* _pRoot;
};