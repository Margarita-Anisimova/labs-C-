#pragma once
#include <iostream>
#include <vector>
using namespace std;


class PlayField
{
public:
	
	enum  State { csEmpty, csCross, csNought };
	enum  GameState { fsInvalid, fsNormal, fsCrossesWin, fsNoughtsWin, fsDraw };

	class CellIdx
	{
	public:
		CellIdx(int, int);
		int get_x();
		int get_y();
	private:		
		int x;
		int y;
	};

	vector<CellIdx> getEmptyCells() const;
	PlayField makeMove(CellIdx);
	GameState checkFieldStatus() const;
	State GetWinState() const;
	State operator[] (CellIdx);	
	State get_nextMove();	
	

private:
	State field[9] = { csEmpty ,csEmpty ,csEmpty ,csEmpty ,csEmpty ,csEmpty ,csEmpty ,csEmpty ,csEmpty };
	State nextMove = csCross; 
	PlayField operator+(CellIdx);
	void change_nextMove(bool);
};




