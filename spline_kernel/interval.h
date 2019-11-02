#pragma once
#include "pch.h"
#include "spline_kernel.h"
#include <tuple>
#include <algorithm>
namespace sml
{
	class MATHLIBRARY_API interval
	{
	public:
		interval() = delete;
		
		interval(double a, double b);
		
		
		double get_step(std::size_t n) const;
		double get_inverse_step(std::size_t n) const;
		double length() const;

		bool is_contains(double t) const;

		const double _aborder;
		const double _bborder;
	};


}