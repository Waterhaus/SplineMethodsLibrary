#include "pch.h"
#include "interval.h"

using namespace std;

sml::interval::interval(double a, double b) :
	_aborder(std::min<double>(a, b)),
	_bborder(std::max<double>(a, b)) {}



double sml::interval::length() const 
{
	return _bborder - _aborder;
}


double sml::interval::get_step(std::size_t n) const
{
	double N = static_cast<double>(n);
	return 
			   (_bborder - _aborder) 
		/ //===========================
					 ( N - 1.);
}
double sml::interval::get_inverse_step(std::size_t n) const
{
	double N = static_cast<double>(n);
	return
				  ( N - 1.)
		/ //===========================
			(_bborder - _aborder);
}

bool sml::interval::is_contains(double t) const 
{
	if (t >= _aborder && t <= _bborder)
		return true;
	else
		return false;
}