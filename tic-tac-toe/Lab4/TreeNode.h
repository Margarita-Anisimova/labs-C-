#pragma once
#include "PlayField.h"
#include <vector>

using namespace std;

class TreeNode
{
public:

	TreeNode(PlayField* , TreeNode*);	
	
	void addChild(TreeNode);
	bool isTerminal();
	int childCount();
	const PlayField& value();
	TreeNode* operator[](int);

private:
	vector<TreeNode> children;
	const PlayField* playField;
	TreeNode* parent;
	int childQty();


};

