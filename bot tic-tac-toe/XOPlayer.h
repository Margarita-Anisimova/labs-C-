#include "TreeNode.h"
#include "PlayField.h"

class XOPlayer
{
public:
	XOPlayer(TreeNode* node, PlayField::State st) : tree(node), state(st) { };
	PlayField::State selectPlayer() const;
	void makeMove(PlayField::CellIdx iCell);
	void makeMove();
	PlayField currentState() const;
	PlayField::GameState fieldStatus() const;
private:
	TreeNode* tree;
	TreeNode& nowNode() const { return (*tree); }
	PlayField::State state;
};

