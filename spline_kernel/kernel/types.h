#pragma once 
#include "spline.h"

namespace spl 
{
	using Vector2 = Eigen::Vector2d;
	using Vector3 = Eigen::Vector3d;
	using Vector4 = Eigen::Vector4d;

	template<std::size_t k>
	using spline = ker::spline<double, k>;
	using simple_spline = spline<2u>;

	template<std::size_t k>
	using spline_curve2d = ker::spline<Vector2, k>;

	template<std::size_t k>
	using spline_curve3d = ker::spline<Vector3, k>;

}
