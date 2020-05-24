#pragma once
#include "PlayField.h"

class Score
{
public:
	Score(int x, int o, int d) : crossesWin(x), noughtsWin(o), draw(d) { }

	void operator+=(const Score& nowResult)
	{
		crossesWin = nowResult.crossesWin + crossesWin;
		noughtsWin = nowResult.noughtsWin + noughtsWin;
		draw = nowResult.draw + draw;
	}

	double getShare(PlayField::State winner) const
	{
		double sum = crossesWin + noughtsWin + draw;
		return (winner == PlayField::csCross) ? (crossesWin + draw) / sum : (noughtsWin + draw) / sum;
	}

private:
	int crossesWin = 0;
	int noughtsWin = 0;
	int draw = 0;
};

