#pragma once
#include <iostream>
#include <vector>

class PlayField
{
public:	
	enum  State { csEmpty, csCross, csNought };
	enum  GameState { fsInvalid, fsNormal, fsCrossesWin, fsNoughtsWin, fsDraw };

	class CellIdx
	{
	public:
		CellIdx(int i, int j) : x(i), y(j) { }
		CellIdx(int i);
		int get_x() { return x; }
		int get_y() { return y; }
		int convertToInt() const;
	private:	
		int x = 0;
		int y = 0;
	};

	PlayField makeMove(CellIdx cell);
	std::vector<CellIdx> getEmptyCells() const;	
	GameState checkFieldStatus() const;
	void checkLine(int start, int end, int step, int& countWin, State& winState) const;
	std::tuple<int, int>  GetCountCrossNought() const;
	State operator[] (CellIdx cell) const;	
	State get_nextMove() const;	
	static int getSize() { return size; }

private:
	static constexpr int size = 3;
	State field[size*size] = { csEmpty };
	PlayField operator+(CellIdx cell);
};

