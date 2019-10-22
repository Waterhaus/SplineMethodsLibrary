#pragma once
#include "pch.h"
#include "spline_kernel.h"
#include <tuple>
#include <algorithm>
namespace spl
{
	class MATHLIBRARY_API interval
	{
	public:
		interval() = delete;
		
		interval(double a, double b);
		
		interval(std::tuple<double, double> ab);

		double get_step(std::size_t n) const;
		double length() const;

		const double _aborder;
		const double _bborder;
	};


}