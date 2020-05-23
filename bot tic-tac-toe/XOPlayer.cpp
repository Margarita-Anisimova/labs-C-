#include "XOPlayer.h"
#include <stdexcept>

PlayField::State XOPlayer::selectPlayer() const
{
	return botState;
}

void XOPlayer::makeMove(PlayField::CellIdx iCell)
{
	if (nowNode->value()[iCell] != PlayField::csEmpty)
		throw std::exception("this cell is already occupied");

	for (int i = 0; i < nowNode->childCount(); i++)
		if (nowNode->operator[](i).value()[iCell] != PlayField::csEmpty)
		{
			nowNode = &nowNode->operator[](i);
			return;
		}
}

void XOPlayer::makeMove()
{
	if (fieldStatus() == PlayField::fsNormal)
	{
		TreeNode* max = &nowNode->operator[](0);
		for (int i = 1; i < nowNode->childCount(); i++)
			if (nowNode->operator[](i).score.getShare(botState) > max->score.getShare(botState))
				max = &nowNode->operator[](i);
		nowNode = max;
	}
}

PlayField XOPlayer::currentState() const
{
	return nowNode->value();
}

PlayField::GameState XOPlayer::fieldStatus() const
{
	return currentState().checkFieldStatus();
}

