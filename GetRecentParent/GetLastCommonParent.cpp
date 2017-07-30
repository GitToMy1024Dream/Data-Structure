
bool GetNodePath(Node* pRoot, Node* pNode, list<Node*>& path)
{
	if (pRoot == NULL)
		return false;
	
	path.push_back(pRoot);
	bool found = false;

	vector<Node*>::iterator it = pRoot->m_Child.begin();
	while (!found && it < pRoot->m_Child.end())
	{
		found = GetNodePath(*it, pNode, path);
		++it;
	}
	if (!found)
		path.pop_back();
	return found;
}

Node* GetLastCommondNode(const list<Node*>& path1,const list<Node*>& path2)
{
	list<Node*>::const_iterator i = path1.begin();
	list<Node*>::const_iterator j = path2.begin();
	Node* Last = NULL;
	while (i != path1.end() && j != path2.end())
	{
		if (*i == *j)
			Last = *i;
		++i;
		++j;
	}
	return Last;
}

Node* GetLastCommondParent(Node* root, Node* node1, Node* node2)
{
	if (root == NULL || node1 == NULL || node2 == NULL)
		return NULL;
	list<Node*> path1;
	list<Node*> path2;
	GetNodePath(root, node1, path1);
	GetNodePath(root, node2, path2);
	return GetLastCommondNode(path1, path2);
}
