#include "interval.h"
#include "pch.h"
using namespace std;

double spl::interval::length() const 
{
	return _bborder - _aborder;
}


double spl::interval::get_step(std::size_t n) const
{
	return (_bborder - _aborder) / (static_cast<double>(n) - 1.0);
}