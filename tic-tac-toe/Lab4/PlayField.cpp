#include "PlayField.h"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


PlayField::CellIdx:: CellIdx(int i, int j)
{
	x = i;
	y = j;	
}

int PlayField::CellIdx::get_x() { return x; }

int PlayField::CellIdx::get_y() { return y; }


vector<PlayField::CellIdx>  PlayField::getEmptyCells() const
{
	vector<CellIdx> emptyCells;
	for (int i = 0; i < 9; ++i)
	{
		if (field[i] == csEmpty)
		{
			CellIdx cell = { i / 3, i % 3 };
			emptyCells.push_back(cell);
		}
	}
	return emptyCells;
}

PlayField PlayField::makeMove(CellIdx cell)
{
	PlayField newField(*this);
	State st = field[cell.get_x() * 3 + cell.get_y()];
	assert(st == csEmpty && checkFieldStatus() != fsInvalid);
	newField.field[cell.get_x() * 3 + cell.get_y() ] = get_nextMove();
	newField.change_nextMove(get_nextMove() != csCross);
	return newField;
}

void PlayField::change_nextMove(bool isCross)
{
	if (isCross)
		nextMove = csCross;
	else
		nextMove = csNought;
}

PlayField::GameState PlayField::checkFieldStatus() const
{
	int countCross=0;
	int countNought=0;

	for (int i = 0; i < 9; ++i)
	{
		switch (field[i])
		{
		case csCross:
			countCross++;
			break;
		case csNought:
			countNought++;
			break;
		default:
			break;
		}
	}
	State winState = GetWinState();	
	if (abs(countCross - countNought) > 1) 
		return fsInvalid;
	switch (winState)
	{
	case csCross:
		return fsCrossesWin;
	case csNought:
		return fsNoughtsWin;
	case csEmpty:
		if (countCross + countNought == 9)
			return fsDraw;
	default:
		return fsNormal;
	}
}

PlayField::State PlayField::GetWinState() const
{
	if (field[0] != csEmpty && field[0] == field[4] && field[0] == field[8])
		return field[0];
	if(field[2] != csEmpty && field[2] == field[4] && field[2] == field[6])
		return field[2];
	else
		for (int i = 0; i < 3; i++)
		{
			int t = i * 3;
			if (field[i * 3] != csEmpty && field[i * 3] == field[i * 3 + 1] && field[i * 3] == field[i * 3 + 2])
				return field[i * 3];
			if (field[i] != csEmpty && field[i] == field[i + 3] && field[i] == field[i + 6])
				return field[i];
		}
	return csEmpty;
}

PlayField::State PlayField::operator[](CellIdx cell)
{
	auto ind = cell.get_x()*3 + cell.get_y();
	assert(sizeof(field) / sizeof(*field) > ind);
	return field[ind];
}

PlayField::State PlayField::get_nextMove() { return nextMove; }

PlayField PlayField::operator+(CellIdx cell) { return makeMove(cell); }
