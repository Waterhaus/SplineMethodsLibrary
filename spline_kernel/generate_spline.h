#pragma once
#include <functional>
#include "kernel\spline.h"

namespace spl::generator
{
	template<typename T = double, std::size_t p = 2>
	ker::spline<T,p> create_spline(std::function<T(double)> func, interval interv, int size)
	{
		/*NOT IMPLEMENTED*/
		return ker::spline<T, p>();
	}

	template<typename T = double>
	ker::spline<T, 2u> create_spline(std::function<T(double)> func, interval interv, int size)
	{
		const auto [a, b] = interv;
		const double step = interv.get_step(size);
		ker::spline<T, 2> sp = ker::spline<T, 2>(size, interv);

		for (int i = 0; i < size; i++)
			sp[i] = func(a + i * step);

		return sp;
	}
}