#pragma once
#include <functional>
#include <optional>
#include "interval.h"

namespace sml::numeric
{

	template<typename T>
	std::optional<double> bisection(	std::function<T(double)> f, 
					interval interv,
					const double epsilon,
					std::function<bool(std::function<T(double)>, interval)> compare) {

		auto [a, b] = interv.data();

		while (b - a > epsilon) {
			double center = 0.5 * (a + b);
			bool left =		compare(f, interval{a, center});
			bool right =	compare(f, interval{center, b});
			if (left && right || !left && !right)
				return std::nullopt;

			if (left)
				b = center;
			else
				a = center;
		}

		return  0.5 * (a + b);
	}

}