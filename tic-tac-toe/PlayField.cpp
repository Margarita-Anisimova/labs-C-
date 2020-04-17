#include "PlayField.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <math.h>
#include <tuple>

using namespace std;

PlayField::CellIdx::CellIdx(int i) 
{
	x = i / size;
	y = i % size;
}

int PlayField::CellIdx::convertToInt() const
{
	return (size * x + y);
}

vector<PlayField::CellIdx>  PlayField::getEmptyCells() const
{
	vector<CellIdx> emptyCells;
	for (int i = 0; i < size * size; ++i)
		if (field[i] == csEmpty)
		{
			CellIdx cell(i);
			emptyCells.push_back(cell);
		}
	return emptyCells;
}

PlayField PlayField::makeMove(CellIdx cell)
{
	State st = field[cell.convertToInt()];
	assert(st == csEmpty && checkFieldStatus() == fsNormal);
	return (*this) + cell;
}

PlayField PlayField::operator+(CellIdx cell)
{
	PlayField newField(*this);
	newField.field[cell.convertToInt()] = get_nextMove();
	return newField;
}

tuple<int , int> PlayField::GetCountCrossNought() const
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

void PlayField::checkLine(int start, int end, int step, int& countWin, State& winState) const
{
	for (int i = start; i <= end; i = i + step)
	{
		if (i == end)
		{
			countWin++;
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
	checkLine(0, size * size - 1, size + 1, countWin, winState);
	checkLine(size - 1, size * size - size, size - 1, countWin, winState);
	for (int i = 0; i < size; i++)
	{
		checkLine(i, i + size * (size - 1), size, countWin, winState);
		checkLine(i * size, i * size + size - 1, 1, countWin, winState);
	}

	auto count = GetCountCrossNought();
	if (abs(get<0>(count) - get<1>(count)) > 1)
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
	assert(size*size > cell.convertToInt());
	return field[cell.convertToInt()];
}

