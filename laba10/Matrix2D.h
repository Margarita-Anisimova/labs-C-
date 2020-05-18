#pragma once
#include "MatrixBase.h"

class Matrix2D : public MatrixBase
{
public:
	Matrix2D() : MatrixBase(s) { }
	virtual int element(unsigned int i, unsigned int j) const override;
	virtual int& element(unsigned int i, unsigned int j) override;
private:
	static constexpr int s = 2;
	int arr[s][s];
};

