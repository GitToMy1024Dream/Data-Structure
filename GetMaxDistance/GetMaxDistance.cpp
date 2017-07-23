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
		int left = _MaxDistance(pRoot->_pLeft, instance);//左子树的最长距离
		int right = _MaxDistance(pRoot->_pRight, instance);//右子树的最长距离
		if ((left + right) > instance) //更新最远距离
			instance = left + right;
		//当前节点的深度+1
		return left > right ? left + 1 : right + 1;
	}