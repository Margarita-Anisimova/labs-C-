#include "PlayField.h"
#include <cassert>
#include <tuple>

using namespace std;

PlayField::CellIdx::CellIdx(int i)
{
	x = i / size;
	y = i % size;
}

PlayField::CellIdx::operator int() const
{
	return (size * x + y);
}

vector<PlayField::CellIdx>  PlayField::getEmptyCells() const
{
	vector<CellIdx> emptyCells;
	for (int i = 0; i < size * size; ++i)
		if (field[i] == csEmpty)
		{
			PlayField::CellIdx cell(i);
			emptyCells.push_back(cell);
		}
	return emptyCells;
}

PlayField PlayField::makeMove(CellIdx cell) const
{
	assert(field[cell] == csEmpty && checkFieldStatus() == fsNormal);
	PlayField newField(*this);
	return newField + cell;
}

PlayField PlayField::operator+(CellIdx cell)
{
	this->field[cell] = get_nextMove();
	return *this;
}

tuple<int, int> PlayField::GetCountCrossNought() const
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
	return make_tuple(countCross, countNought);
}

PlayField::State PlayField::get_nextMove() const
{
	auto count = GetCountCrossNought();
	int difference = get<0>(count) - get<1>(count);
	assert(difference == 0 || difference == 1);
	return  difference == 1 ? csNought : csCross;
}

PlayField::State PlayField::getWinnerState(bool& isInvalid) const
{
	State winState = csEmpty;
	CellIdx startLine(0, 0);
	for (int i = 1; i < size; ++i)
	{
		if (field[startLine] == csEmpty || field[startLine] != field[*new CellIdx(i, i)])
			break;
		if (i == size - 1)
			winState = field[startLine];
	}
	if (winState == csEmpty)
	{
		startLine = { 0, size - 1 };
		for (int i = 1; i < size; ++i)
		{
			if (field[startLine] == csEmpty || field[startLine] != field[*new CellIdx(i, size - 1 - i)])
				break;
			if (i == size - 1)
				winState = field[startLine];
		}
		if (winState == csEmpty)
		{
			for (int i = 0; i < size; ++i)
			{
				startLine = { i, 0 };
				for (int j = 1; j < size; ++j)
				{
					if (field[startLine] == csEmpty || field[startLine] != field[*new CellIdx(i, j)])
						break;
					if (j == size - 1)
						if (winState != csEmpty)
							isInvalid = true;
						else
							winState = field[startLine];
				}
			}
			if (winState == csEmpty)
				for (int i = 0; i < size; ++i)
				{
					startLine = { 0, i };
					for (int j = 1; j < size; ++j)
					{
						if (field[startLine] == csEmpty || field[startLine] != field[*new CellIdx(j, i)])
							break;
						if (j == size - 1)
							if (winState != csEmpty)
								isInvalid = true;
							else
								winState = field[startLine];
					}
				}
		}
	}
	return winState;
}

PlayField::GameState PlayField::checkFieldStatus() const
{
	int countWin = 0;
	int difference = get<0>(count) - get<1>(count);
	if (!(difference == 0 || difference == 1))
		return fsInvalid;
	bool isInvalide = false;
	auto winState = getWinnerState(isInvalide);
	if (isInvalide)
		return fsInvalid;
	switch (winState)
	{
	case csCross:
		return fsCrossesWin;
	case csNought:
		return fsNoughtsWin;
	case csEmpty:
		if (get<0>(count) + get<1>(count) == size * size)
			return fsDraw;
	default:
		return fsNormal;
	}
}

PlayField::State PlayField::operator[](CellIdx cell) const
{
	assert(size * size > cell);
	return field[cell];
}

