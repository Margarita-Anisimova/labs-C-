#include "Matrix2D.h"
#include <iostream>

int Matrix2D::element(unsigned int i, unsigned int j) const
{
	return arr[i][j];
}

int& Matrix2D::element(unsigned int i, unsigned int j)
{
	return arr[i][j];
}

