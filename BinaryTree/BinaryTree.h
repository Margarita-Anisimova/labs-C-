#pragma once
#include "TreeNode.h"


class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();
	BinaryTree(int h);
	void Insert(int value);
	TreeNode* Search(int value);
private:
	void deleteTree(TreeNode* head);
	TreeNode* head;
	void Insert(int value, TreeNode* node);
	TreeNode* Search(int value, TreeNode* node);
};
