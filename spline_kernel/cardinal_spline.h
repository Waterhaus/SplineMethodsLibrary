#pragma once
#include <vector>

namespace spl::cardinal
{
	//функция - ступенька на отрезке [0,1]
	double rect(double t);
	double ksi(double t, std::size_t k);
}