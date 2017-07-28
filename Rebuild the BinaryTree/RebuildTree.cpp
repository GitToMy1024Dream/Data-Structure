#include <iostream>
#include <vector>
using namespace std;


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL)
	{}
};

class Solution {
public:
	TreeNode* reConstructBinaryTree(vector<int> pre, vector<int> vin)
	{
		if (pre.size() <= 0 || vin.size() <= 0)
			return NULL;
		return reConstructBinaryTree(pre, 0, pre.size() - 1, vin, 0, vin.size() - 1);
	}
private:
	TreeNode* reConstructBinaryTree(vector<int> &pre, int preBegin, int preEnd, vector<int> vin, int vinBegin, int vinEnd)
	{
		if (preBegin > preEnd || vinBegin > vinEnd)
			return NULL;
		TreeNode* root = new TreeNode(pre[preBegin]);
		for (int i = 0; i <= preEnd; i++)
		{
			if (vin[i] == pre[preBegin])
			{
				root->left = reConstructBinaryTree(pre, preBegin + 1, preBegin + i - vinBegin, vin, vinBegin, i - 1);
				root->right = reConstructBinaryTree(pre, i - vinBegin + preBegin + 1, preEnd, vin, i + 1, vinEnd);
			}
		}
		return root;
	}
};


void Test()
{
	vector<int> pre = { 1, 2, 4, 7, 3, 5, 6, 8 };
	vector<int> vin = { 4, 7, 2, 1, 5, 3, 8, 6 };
	Solution *s = NULL;
	s->reConstructBinaryTree(pre, vin);
}
int main()
{
	Test();
	system("pause");
	return 0;
}