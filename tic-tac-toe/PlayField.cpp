#include "PlayField.h"
#include <cassert>

using namespace std;

PlayField::CellIdx::operator int() const
{
	return (size * x + y);
}

vector<PlayField::CellIdx>  PlayField::getEmptyCells() const
{
	vector<CellIdx> emptyCells;
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
		{
			PlayField::CellIdx cell(i, j);
			if (field[cell] == csEmpty)
				emptyCells.push_back(cell);
		}
	return emptyCells;
}

PlayField PlayField::makeMove(CellIdx cell) const
{
	return *this + cell;
}

PlayField PlayField::operator+(CellIdx cell) const
{
	assert(field[cell] == csEmpty && checkFieldStatus() == fsNormal);
	PlayField newField(*this);
	newField.field[cell] = get_nextMove();
	return newField;
}

int PlayField::GetDifferenceCrossNought() const
{
	int countCross = 0;
	int countNought = 0;
	for (int i = 0; i < size * size; ++i)
		switch (field[i])
		{
		case csCross:
			countCross++;
			break;
		case csNought:
			countNought++;
			break;
		}
	return countCross - countNought;
}

PlayField::State PlayField::get_nextMove() const
{
	int difference = GetCountCrossNought();
	assert(difference == 0 || difference == 1);
	return  difference == 1 ? csNought : csCross;
}

PlayField::State PlayField::checkDiagonals(bool isMain) const
{
	int start = isMain ? 0 : size - 1;
	for (int i = 1; i < size; i++)
	{
		CellIdx cell = isMain ? CellIdx(i, i) : CellIdx(i, start - i);
		if (field[cell] == csEmpty || field[start] != field[cell])
			return csEmpty;
	}
	return field[start];
}

PlayField::GameState PlayField::checkLines(bool isVertical) const
{
	State winState = csEmpty;
	for (int i = 0; i < size; i++)
	{
		CellIdx start = isVertical ? CellIdx(0, i) : CellIdx(i, 0);
		for (int j = 1; j < size; j++)
		{
			CellIdx cell = isVertical ? CellIdx(j, i) : CellIdx(i, j);
			if (field[cell] == csEmpty || field[cell] != field[start])
				break;
			if (j == size - 1)
				if (winState != csEmpty)
					return fsInvalid;
				else
					winState = field[start];
		}
	}
	switch (winState)
	{
	case csCross:
		return fsCrossesWin;
	case csNought:
		return fsNoughtsWin;
	default:
		return fsNormal;
	}
}

PlayField::GameState PlayField::checkFieldStatus() const
{
	int difference = GetDifferenceCrossNought();
	if (difference != 0 && difference != 1)
		return fsInvalid;
	State winnerDiagonal = checkDiagonals(true);
	winnerDiagonal = winnerDiagonal == csEmpty ? checkDiagonals(false) : winnerDiagonal;
	if (winnerDiagonal == csEmpty)
	{
		GameState winState;
		winState = checkLines(true);
		winState = winState == fsNormal ? checkLines(false) : winState;
		if (winState == fsNormal)
			return getEmptyCells().size() == 0 ? fsDraw : fsNormal;
		return winState;
	}
	switch (winnerDiagonal)
	{
	case csCross:
		return fsCrossesWin;
	case csNought:
		return fsNoughtsWin;
	}
}

PlayField::State PlayField::operator[](CellIdx cell) const
{
	assert(size * size > cell);
	return field[cell];
}

