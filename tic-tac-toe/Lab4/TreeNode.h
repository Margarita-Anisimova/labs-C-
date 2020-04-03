#pragma once
#include "PlayField.h"
#include <vector>

using namespace std;

class TreeNode
{
public:

	TreeNode(PlayField* , TreeNode*);	
	
	void addChild(TreeNode);
	bool isTerminal() const;
	int childCount() const;
	const PlayField& value() const;
	TreeNode* operator[](int);

private:
	vector<TreeNode> children;
	const PlayField* playField;
	TreeNode* parent;
	int childQty() const;


};

