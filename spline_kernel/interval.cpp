#include "pch.h"
#include "interval.h"

using namespace std;


spl::interval::interval() :
	_aborder(0.),
	_bborder(0.) {}

spl::interval::interval(double a, double b) :
	_aborder(std::min<double>(a, b)),
	_bborder(std::max<double>(a, b)) {}


double spl::interval::length() const 
{
	return _bborder - _aborder;
}


double spl::interval::get_step(std::size_t n) const
{
	double N = static_cast<double>(n);
	return 
			   (_bborder - _aborder) 
		/ //===========================
					 ( N - 1.);
}
double spl::interval::get_inverse_step(std::size_t n) const
{
	double N = static_cast<double>(n);
	return
				  ( N - 1.)
		/ //===========================
			(_bborder - _aborder);
}

bool spl::interval::is_contains(double t) const 
{
	if (t >= _aborder && t <= _bborder)
		return true;
	else
		return false;
}

std::tuple<double, double> spl::interval::data() const 
{
	return std::make_tuple(_aborder, _bborder);
}
