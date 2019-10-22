#include "pch.h"
#include "interval.h"

using namespace std;

spl::interval::interval(double a, double b) :
	_aborder(std::min<double>(a, b)),
	_bborder(std::max<double>(a, b)) {}

spl::interval::interval(std::tuple<double, double> ab) :
	_aborder(std::min<double>(std::get<0>(ab), std::get<1>(ab))),
	_bborder(std::max<double>(std::get<0>(ab), std::get<1>(ab))) {}



double spl::interval::length() const 
{
	return _bborder - _aborder;
}


double spl::interval::get_step(std::size_t n) const
{
	return (_bborder - _aborder) / (static_cast<double>(n) - 1.0);
}