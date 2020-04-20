#pragma once
class TreeNode
{
public:
	TreeNode();
	TreeNode(int val);
	int getValue() const { return value; }
	TreeNode* getLeft() const { return left; }
	TreeNode* getRight() const { return right; }
	void setLeft(TreeNode* l);
	void setValue(int val);
	void setRight(TreeNode* r);
private:
	int value;
	TreeNode* left;
	TreeNode* right;
};
