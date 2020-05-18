
#include "MatrixBase.h"

class Matrix3D : public MatrixBase
{
public:
	Matrix3D() : MatrixBase(s) { }
	virtual int element(unsigned int i, unsigned int j) const override;
	virtual int& element(unsigned int i, unsigned int j) override;

private:
	static constexpr int s = 3;
	int arr[s][s] = {0};
};

