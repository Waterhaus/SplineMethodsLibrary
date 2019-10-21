#pragma once
#include "pch.h"
#include <tuple>
#include <algorithm>
namespace spl
{
	class interval
	{
	public:
		interval() = delete;
		interval(double a, double b) : _aborder(std::min<double>(a, b)), _bborder(std::max<double>(a, b)) {}
		interval(std::tuple<double, double> ab) :
			_aborder(std::min<double>(std::get<0>(ab), std::get<1>(ab))),
			_bborder(std::max<double>(std::get<0>(ab), std::get<1>(ab))) {}


		double get_step(std::size_t n) const;
		double length() const;

	private:
		const double _aborder;
		const double _bborder;
	};


}