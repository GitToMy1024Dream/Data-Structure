int MaxDistance()
	{ 
		int distance = 0;
		_MaxDistance(_pRoot,distance);
		return distance;
	}
 
int _MaxDistance(Node* pRoot, int& instance)
	{
		if (pRoot == NULL)
			return 0;
		int left = _MaxDistance(pRoot->_pLeft, instance);//�������������
		int right = _MaxDistance(pRoot->_pRight, instance);//�������������
		if ((left + right) > instance) //������Զ����
			instance = left + right;
		//��ǰ�ڵ�����+1
		return left > right ? left + 1 : right + 1;
	}