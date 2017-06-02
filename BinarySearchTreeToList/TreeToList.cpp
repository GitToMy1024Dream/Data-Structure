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
	Node*& Transfrom(const Node* _pRoot)//_pRootΪ���ĸ��ڵ�
	{
		Node* _prev = NULL;//��¼�����ǰһ���ڵ�
		_Transfrom(_pRoot,_prev);//BST->LIST
		while (_pRoot->_pLeft)//������ߵĽ�㼴�����ͷ
			_pRoot = _pRoot->_pLeft;
		return _pRoot;
	}
protected:
	void _Transfrom(const Node* root, Node* _prev)
	{
		//����
		if (root == NULL)
			return NULL;
		Node* pCur = root;
		_Transfrom(pCur->_pLeft, _prev);//�ݹ�������
		if (_prev)
		{
			_prev->_pRight = pCur;
		}
		pCur->_pLeft = _prev;
		_prev = pCur;
		_Transfrom(pCur->_pRight, _prev);//��������ݹ�������
	}
private:
	Node* _pRoot;
};