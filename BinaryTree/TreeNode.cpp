#include "TreeNode.h"

TreeNode::TreeNode()
{
	value = 0;
	left = nullptr;
	right = nullptr;
}

TreeNode::TreeNode(int val)
{
	value = val;
	left = nullptr;
	right = nullptr;
}

void TreeNode::setLeft(TreeNode* l)
{
	left = l;
}

void TreeNode::setValue(int val)
{
	value = val;
}

void TreeNode::setRight(TreeNode* r)
{
	right = r;
}
