#include "XOPlayer.h"

PlayField::State XOPlayer::selectPlayer() const
{
	return state;
}

void XOPlayer::makeMove(PlayField::CellIdx iCell)
{
	if (tree->value()[iCell] == PlayField::csEmpty)
	{
		for (int i = 0; i < tree->childCount(); i++)
			if (nowNode()[i].value()[iCell] != PlayField::csEmpty)
			{
				tree = &(*tree)[i];
				return;
			}
	}
	else
		throw 1;
}

void XOPlayer::makeMove()
{
	if (fieldStatus() == PlayField::fsNormal)
	{
		TreeNode* max = &nowNode()[0];
		for (int i = 1; i < tree->childCount(); i++)
		{
			if (nowNode()[i].score.getShare(state) > max->score.getShare(state))
				max = &nowNode()[i];
		}
		tree = max;
	}
}

PlayField XOPlayer::currentState() const
{
	return tree->value();
}

PlayField::GameState XOPlayer::fieldStatus() const
{
	return currentState().checkFieldStatus();
}

