#pragma once
#include <vector>
#include <Eigen/Dense>
#include <optional>
#include "interval.h"
#include "cardinal_spline.h"



namespace spl::ker
{

	template <typename T>
	using Vector = Eigen::Matrix<T, Eigen::Dynamic, 1>;

	//VectorSpaceType - {+,-, * (on double) }
	//degree -
	template<typename VectorSpaceType, std::size_t degree>
	class spline
	{
	public:
		spline();
		spline(std::size_t grid_size, interval border);
		spline(const spline& f);
		
		~spline() {};

	
		std::size_t size() const { return _coefs.size(); }
		interval domain() const {
			const auto [a, b] = _border;
			const double delta = ((double)degree - 1.) * _step;
			return interval(a - delta, b +  delta); 
		}
		

		VectorSpaceType& operator[](std::size_t idx) { return _coefs[idx]; }
		const VectorSpaceType& operator[](std::size_t idx) const { return _coefs[idx]; }

	
		VectorSpaceType operator()(double t) const;

		/*======================================================*
		** addition and subtraction.
		*=======================================================*/
		spline operator+(const spline& other) const;
		spline operator-(const spline& other) const;
		
		/*======================================================*
		** multyplication left and right.
		*=======================================================*/

		template<typename T, std::size_t p>
		friend spline<T, p> operator* (double a, const spline<T, p>& f);
		
		
		template<typename T, std::size_t p>
		friend spline<T, p> operator* (const spline<T, p>& f, double a);

	private:

		Vector<VectorSpaceType> _coefs;
		interval _border;
		double _step;
		std::size_t _grid_size;

	};

}
#include "spline.hpp"
