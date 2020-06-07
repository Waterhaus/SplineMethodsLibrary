#pragma once
#include <functional>
#include "spline.h"

namespace sml::generator
{
	template<typename T = double, std::size_t p = 2>
	spline<T,p> create_spline(std::function<T(double)> func, interval interv, int size)
	{
		/*NOT IMPLEMENTED*/
		return spline<T, p>();
	}

	template<typename T = double>
	spline<T, 2u> create_spline(std::function<T(double)> func, interval interv, int size)
	{
		const auto [a, b] = interv;
		const double step = interv.get_step(size);
		spline<T, 2> sp = spline<T, 2>(size, interv);

		for (int i = 0; i < size; i++)
			sp[i] = func(a + i * step);

		return sp;
	}
}