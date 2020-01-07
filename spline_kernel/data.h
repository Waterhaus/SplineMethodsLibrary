#pragma once
#include <vector>
#include "interval.h"

namespace sml::data
{
	template<typename T, typename F>
	std::vector<T> calculate_points(const F& f, interval interv, int size)
	{
		std::vector<T> data(size);
		const auto [a, b] = interv;
		const double step = interv.get_step(size);
		
		for (size_t i = 0; i < size; i++)
			data[i] = f(a + i * step);
		
		return data;
	}
}