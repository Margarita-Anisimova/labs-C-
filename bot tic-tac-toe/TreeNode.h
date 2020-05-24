#pragma once
#include "PlayField.h"
#include "Score.h"
#include <vector>

class TreeNode
{
public:	
	TreeNode(PlayField field) : playField(field), score(0,0,0) { }
	~TreeNode();
	void addChild(TreeNode* child);
	bool isTerminal() const;
	int childCount() const;
	const PlayField& value() const;
	TreeNode& operator[](int i) const;
	Score score;
private:
	const PlayField playField;
	TreeNode* parent = nullptr;
	std::vector<TreeNode*> children;
	int childQty() const;
};

