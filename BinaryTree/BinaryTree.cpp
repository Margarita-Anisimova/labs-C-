#include "BinaryTree.h"
#include <cassert>

BinaryTree::BinaryTree()
{
	head = nullptr;
}

BinaryTree::~BinaryTree()
{
	deleteTree(head);
}

void BinaryTree::deleteTree(TreeNode* head)
{
	if (head != nullptr)
	{
		deleteTree(head->getLeft());
		deleteTree(head->getRight());
		delete head;
	}		
}

BinaryTree::BinaryTree(int h)
{
	head = new TreeNode(h);
}

void BinaryTree::Insert(int value)
{
	Insert(value, head);
}

TreeNode* BinaryTree::Search(int value)
{
	return Search(value, head);
}

void BinaryTree::Insert(int value, TreeNode* node)
{
	if (!node)
		this->head = new TreeNode(value);
	else
	{
		if (value < node->getValue())
			if (node->getLeft())
				Insert(value, node->getLeft());
			else
				node->setLeft(new TreeNode(value));
		if (value > node->getValue())
			if (node->getRight())
				Insert(value, node->getRight());
			else
				node->setRight(new TreeNode(value));
	}
}

TreeNode* BinaryTree::Search(int value, TreeNode* node)
{
	assert(node);
	if (value == node->getValue())
		return node;
	if (value < node->getValue())
		Search(value, node->getLeft());
	else 
		Search(value, node->getRight());
}
