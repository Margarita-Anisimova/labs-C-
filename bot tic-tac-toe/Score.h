#pragma once
#include "PlayField.h"

class Score
{
	public:
		Score(int w, int l, int d) : win(w), lose(l), draw(d) { }
		void operator+=(Score nowResult)
		{
			win = nowResult.win + win;
			lose = nowResult.lose + lose;
			draw = nowResult.draw + draw;
		}		
		int getShare(PlayField::State winner) const;
	private:
		int win = 0;
		int lose = 0;
		int draw = 0;	
};

