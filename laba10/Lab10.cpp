#include "Matrix2D.h"
#include "Matrix3D.h"
#include <iostream>
using namespace std;

void fillArray(MatrixBase& matrix)
{
    for (auto i = 0; i < matrix.size(); i++)
        for (auto j = 0; j < matrix.size(); j++)
            matrix.element(i, j) = i * matrix.size() + j + 1;
}

int main()
{
    Matrix2D m2a, m2b;
    Matrix3D m3a, m3b;
    fillArray(m2a);
    fillArray(m2b);
    fillArray(m3a);
    fillArray(m3b);
    cout << "Start matrix:" << endl;
    cout << m2a << endl;
    cout << m2b << endl;
    cout << m3a << endl;
    cout << m3b << endl;    
    cout << m3a << endl;
    m2a *= 5;
    cout << "m2a * 5" << endl << m2a << endl;
    m2b *= 6;
    cout << "m2b * 6" << endl << m2b << endl;
    m3a *= 3;
    cout << "m3a * 3" << endl << m3a  << endl;
    m3b *= 2;
    cout << "m3b * 2" << endl << m3b << endl;
    m2a += m2b;
    cout << "m2a + m2b" << endl << m2a << endl;
    m3a += m3b;
    cout << "m3a + m3b" << endl << m3a << endl;
    return 0;
}

