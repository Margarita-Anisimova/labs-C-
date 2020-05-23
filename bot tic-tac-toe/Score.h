#pragma once
#include "PlayField.h"

class Score
{
public:
	Score(int x, int o, int d) : crossesWin(x), noughtsWin(o), draw(d) { }

	void operator+=(Score nowResult)
	{
		crossesWin = nowResult.crossesWin + crossesWin;
		noughtsWin = nowResult.noughtsWin + noughtsWin;
		draw = nowResult.draw + draw;
	}

	int getShare(PlayField::State winner) const
	{
		return (winner == PlayField::csCross) ? crossesWin + draw : noughtsWin + draw;
	}

private:
	int crossesWin = 0;
	int noughtsWin = 0;
	int draw = 0;
};

