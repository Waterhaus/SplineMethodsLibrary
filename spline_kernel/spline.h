#pragma once
#include <vector>
#include <Eigen/Dense>
#include "interval.h"
#include "cardinal_spline.h"



namespace sml
{

	template <typename T>
	using Vector = Eigen::Matrix<T, Eigen::Dynamic, 1>;

	//VectorSpaceType - тип, поддерживающий операции векторного пространства +,-,*, умножение на число и так далее
	//degree - степень сплайна
	template<typename VectorSpaceType, std::size_t degree>
	class spline
	{
	public:
		spline();
		spline(std::size_t grid_size, interval border);//выделение памяти. создаем вектор размера size + degree - 2
		spline(const spline& f);

		~spline() {};

		//функции наследники vector
		std::size_t size() const { return _coefs.size(); }
		void resize(std::size_t grid_size) 
		{ 
			_grid_size = grid_size;
			_coefs.resize(grid_size);
			_coefs = Vector<VectorSpaceType>::Zero();
		}
		

		VectorSpaceType& operator[](std::size_t idx) { return _coefs[idx]; }
		const VectorSpaceType& operator[](std::size_t idx) const { return _coefs[idx]; }

		//f(t) -> VectorSpaceType. это тип коэффициентов
		VectorSpaceType operator()(double t) const;

		spline operator+(const spline& other) const;
		spline operator*(double val);

	private:
		
		Vector<VectorSpaceType> _coefs;
		interval _border;
		std::size_t _grid_size;

	};


}
#include "spline.hpp"
