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
	return (_bborder - _aborder) / (static_cast<double>(n) - 1.0);
}

bool sml::interval::is_contains(double t) const 
{
	if (t >= _aborder && t <= _bborder)
		return true;
	else
		return false;
}