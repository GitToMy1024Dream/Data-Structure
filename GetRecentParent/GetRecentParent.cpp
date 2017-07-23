Node* GetRecentParent(Node* pNode1,Node* pNode2) 
	{
		return _GetRecentParent(_pRoot, pNode1, pNode2);
	}
//获取pNode的路径，保存在栈中
bool _GetPath(Node* pRoot, Node* pNode, stack<Node*>& s)
	{
		s.push(pRoot);
		while (pNode->_data == pRoot->_data)
			return true;
		if (_GetPath(pRoot->_pLeft, pNode, s))
			return true;
		if (_GetPath(pRoot->_pRight, pNode, s))
			return true;
		s.pop();
		return false;
	}
//二叉树中两个节点的最近公共祖先
Node* _GetRecentParent(Node* pRoot, Node* pNode1, Node* pNode2)
	{
		if (pRoot == NULL || pNode1 == NULL || pNode2 == NULL)
			return NULL;
		stack<Node*> _s1;//保存节点1经过的路径
		stack<Node*> _s2;//保存节点2经过的路径
		_GetPath(pRoot, pNode1, _s1);
		_GetPath(pRoot, pNode2, _s2);
		//保证两个栈的结点个数一致，再一起出栈，直到栈顶元素相等
		while (_s1.size() > _s2.size())
			_s1.pop();
		while (_s1.size() < _s2.size)
			_s2.pop();
		while (_s1.top() != _s2.top())
		{
			_s1.pop();
			_s2.pop();
		}
		return _s1.top();
	}