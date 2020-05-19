#include "Score.h"

int Score::getShare(PlayField::State winner) const
{
	if (win == 0 && lose == 0 && draw == 0)
		return 1;
	return (winner == PlayField::csCross) ? win + draw : lose + draw;
}

