#include "TreeNode.h"
#include <cassert>

TreeNode::TreeNode(PlayField* field, TreeNode* node)
{
	playField = field;
	parent = node;
}

void TreeNode::addChild(TreeNode child) 
{
	assert(childQty() > childCount());
	children.push_back(child);
}

bool TreeNode::isTerminal() const 
{
	return (childQty() == 0 || (*playField).checkFieldStatus() != PlayField::fsNormal);
}

int TreeNode::childCount() const
{
	return children.size();
}

const PlayField& TreeNode::value() const
{
	return *playField;
}

TreeNode* TreeNode::operator[](int i) 
{
	assert(children.size() > i);
	return &children[i];
}

int TreeNode::childQty() const
{
	return (*playField).getEmptyCells().size();
}
