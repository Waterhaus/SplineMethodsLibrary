#pragma once
#include <vector>

namespace spl::cardinal
{
	//функци€ - ступенька на отрезке [0,1]
	double rect(double t);

	//рекурсивное вычисление кардинального сплайна пор€ка k в точке t
	double ksi(double t, int k);
}