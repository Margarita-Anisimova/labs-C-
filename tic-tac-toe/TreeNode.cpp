#include "TreeNode.h"
#include <cassert>

using namespace std;

TreeNode::~TreeNode()
{
	for(auto child : children)
		delete child;
}

void TreeNode::addChild(TreeNode* child) 
{
	if (!child)
		return;
	assert(childQty() > childCount());
	child->parent = this;
	children.push_back(child);
}

bool TreeNode::isTerminal() const 
{
	auto fieldState = playField.checkFieldStatus();
	return (childQty() == 0 || fieldState == PlayField::fsCrossesWin 
		|| fieldState == PlayField::fsNoughtsWin);
}

int TreeNode::childCount() const
{
	return children.size();
}

const PlayField& TreeNode::value() const
{
	return playField;
}

TreeNode& TreeNode::operator[](int i) const
{
	return *children[i];
}

int TreeNode::childQty() const
{
	return playField.getEmptyCells().size();
}

