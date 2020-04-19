#include "PlayField.h"
#include <iostream>
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
		default:
			break;
		}
	return make_tuple(countCross, countNought);
}

PlayField::State PlayField::get_nextMove() const
{
	auto count = GetCountCrossNought();
	return (get<0>(count) > get<1>(count)) ? csNought : csCross;
}

void PlayField::checkLine(int start, int end, int step, State& winState) const
{
	for (int i = start; i <= end; i = i + step)
	{
		if (i == end)
		{
			winState = field[i];
			break;
		}
		if (field[i] == csEmpty || field[i] != field[i + step])
			break;
	}
}

PlayField::GameState PlayField::checkFieldStatus() const
{
	int countWin = 0;
	State winState = csEmpty;
	checkLine(0, size * size - 1, size + 1, winState);
	checkLine(size - 1, size * size - size, size - 1, winState);
	for (int i = 0; i < size; i++)
	{
		checkLine(i, i + size * (size - 1), size, winState);
		if (winState != csEmpty)
			countWin++;
		checkLine(i * size, i * size + size - 1, 1, winState);
		if (winState != csEmpty)
			countWin++;
	}

	auto count = GetCountCrossNought();
	if (abs(get<0>(count) - get<1>(count)) > 1 && countWin > 1)
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

