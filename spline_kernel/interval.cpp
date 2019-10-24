#include "pch.h"
#include "interval.h"

using namespace std;

spl::interval::interval(double a, double b) :
	_aborder(std::min<double>(a, b)),
	_bborder(std::max<double>(a, b)) {}



double spl::interval::length() const 
{
	return _bborder - _aborder;
}


double spl::interval::get_step(std::size_t n) const
{
	return (_bborder - _aborder) / (static_cast<double>(n) - 1.0);
}