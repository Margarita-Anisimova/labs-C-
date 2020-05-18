#include "MatrixBase.h"
#include <iostream>


unsigned int MatrixBase::size() const
{
	return m_size;
}

void MatrixBase::operator*=(int iMult)
{
	for (auto i = 0; i < m_size; i++)
		for (auto j = 0; j < m_size; j++)
		{
			element(i, j) *= iMult;
		}
}

void MatrixBase::operator+=(MatrixBase& iAdd)
{
	for (auto i = 0; i < m_size; i++)
		for (auto j = 0; j < m_size; j++)
		{
			element(i, j) += iAdd.element(i, j);
		}
}

std::ostream& operator<<(std::ostream& stream, const MatrixBase& iMatrix)
{
	for (int i = 0; i < iMatrix.size(); i++)
	{
		for (int j = 0; j < iMatrix.size(); j++)
		{
			std::cout << iMatrix.element(i, j) << " ";
		}
		std::cout << std::endl;
	}
	return stream;
}
