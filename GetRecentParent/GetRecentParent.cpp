Node* GetRecentParent(Node* pNode1,Node* pNode2) 
	{
		return _GetRecentParent(_pRoot, pNode1, pNode2);
	}
//��ȡpNode��·����������ջ��
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
//�������������ڵ�������������
Node* _GetRecentParent(Node* pRoot, Node* pNode1, Node* pNode2)
	{
		if (pRoot == NULL || pNode1 == NULL || pNode2 == NULL)
			return NULL;
		stack<Node*> _s1;//����ڵ�1������·��
		stack<Node*> _s2;//����ڵ�2������·��
		_GetPath(pRoot, pNode1, _s1);
		_GetPath(pRoot, pNode2, _s2);
		//��֤����ջ�Ľ�����һ�£���һ���ջ��ֱ��ջ��Ԫ�����
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