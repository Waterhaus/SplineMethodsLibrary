#pragma once
#include "spline.h"
namespace sml 
{
	template<typename VectorSpaceType, std::size_t degree>
	spline<VectorSpaceType, degree>::spline() :
		_coefs(Vector<VectorSpaceType>::Zero(4u + degree - 2u)),
		_border({ 0., 1. }),
		_step(_border.get_step(4)),
		_grid_size(4u) {}



	template<typename VectorSpaceType, std::size_t degree>
	spline<VectorSpaceType, degree>::spline(std::size_t grid_size, interval border) :
		_coefs(Vector<VectorSpaceType>::Zero(grid_size + degree - 2u)),
		_border(border),
		_step(_border.get_step(grid_size)),
		_grid_size(grid_size) {}

	template<typename VectorSpaceType, std::size_t degree>
	spline<VectorSpaceType, degree>::spline(const spline& f) :
		_coefs(f._coefs),
		_border(f._border),
		_grid_size(f._grid_size) {}

//
//	template<typename U, typename T>
//	T part_dot(const U& x, const std::vector<double>& y)
//	{
//		T tmp = 0. * x(0);
//		for (int i = 0; i < y.size(); i++)
//			tmp += x(i) * y[i];
//		return tmp;
//	}
//
//	template<typename VectorSpaceType, std::size_t degree>
//	VectorSpaceType spline<VectorSpaceType, degree>::operator()(double t) const
//	{
//		using vector = std::vector<double>;
//
//		auto filter = [](double t)->double
//		{
//			if (t < 0.) return 0.;
//			if (t > 1.) return 1.;
//			return t;
//		};
//		/*Возвращаемый результат. Аналог 0 в VectorSpaceType*/
//		VectorSpaceType sum = 0. * _coefs(0);
//
//		const int index = cardinal::calculate_relative_index(t, _border, _grid_size);
//		const auto& [a, b] = _border;
//		const double inv_step = _border.get_inverse_step(_grid_size);
//		const double step = _border.get_step(_grid_size);
//		const double x = filter((t - (a + index * step)) * inv_step);
//
//		const vector ksi_val = [x](int deg, int index, int grid_size) {
//
//			auto val = cardinal::bsplvb(x, deg);
//
//			if (index >= 0 && index < grid_size)
//				return val;
//			else {
//				int delta = (index < 0) ? (index) : (index - grid_size + 1);
//
//				/*Если мы за носителем, возвращаем пустой вектор*/
//				if (std::abs(delta) >= deg)
//					return vector();
//
//				if (delta < 0)
//					return vector(val.begin() + std::abs(delta), val.end());
//				else
//					return vector(val.begin(), val.end() - delta);
//			}
//		}(degree, index, _grid_size);
//
//		/*Если индекс в диапозоне 0 <= index < grid_size
//		* тогда используем подмассив из _coefs размера degree */
//		
//		
//		auto block = _coefs.segment(index, degree);
//		sum = part_dot<decltype(block), VectorSpaceType>(block, ksi_val);
//
//		return sum;
//	}

	//=======================================

	template<typename VectorSpaceType, std::size_t degree>
	VectorSpaceType spline<VectorSpaceType, degree>::operator()(double t) const
	{
		using std::vector;
		using std::optional;
		using vector_opt = vector<optional<VectorSpaceType>>;

		auto filter = [](double t)->double {
			if (t < 0.) return 0.;
			if (t > 1.) return 1.;
			return t;
		};

		VectorSpaceType sum = 0. * _coefs(0);
		if (!domain().is_contains(t))
			return sum;

		const int index = cardinal::calculate_relative_index(t, _border, _grid_size);
		const auto& [a, b] = _border;
		const double inv_step = _border.get_inverse_step(_grid_size);
		const double step = _border.get_step(_grid_size);
		const double x = filter((t - (a + index * step)) * inv_step);

		const vector<double> ksi_val = cardinal::bsplvb(x, degree);
		vector_opt c(ksi_val.size());

		for (int k = index, i = 0; k < index + (int)c.size(); ++k, ++i) {
			if (0 <= k && k < _coefs.size())
				c[i] = _coefs[k];
			else
				c[i] = std::nullopt;
		}

		for (int k = 0; k < c.size(); ++k) {
			if (c[k].has_value())
				sum = sum + (ksi_val[k] * c[k].value());
		}

		return sum;
	}


	//=======================================


	template<typename VectorSpaceType, std::size_t degree>
	spline<VectorSpaceType, degree> spline<VectorSpaceType, degree>::operator+(const spline& other) const
	{
		spline<VectorSpaceType, degree> f(_grid_size, _border);
		f._coefs = _coefs + other._coefs;
		return std::move(f);
	}

	template<typename VectorSpaceType, std::size_t degree>
	spline<VectorSpaceType, degree> spline<VectorSpaceType, degree>::operator-(const spline& other) const
	{
		spline<VectorSpaceType, degree> f(_grid_size, _border);
		f._coefs = _coefs - other._coefs;
		return std::move(f);
	}

	template<typename T, std::size_t degree>
	spline<T, degree>  operator*(double a, const spline<T, degree>& other)
	{
		spline<T, degree> f(other._grid_size, other._border);
		other._coefs *= a;

		return std::move(f);
	}

	template<typename T, std::size_t degree>
	spline<T, degree>  operator*(const spline<T, degree>& f, double a)
	{
		return std::move(a * f);
	}
}
