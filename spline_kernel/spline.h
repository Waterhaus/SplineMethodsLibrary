#pragma once
#include <vector>
#include "interval.h"
#include "cardinal_spline.h"

namespace sml
{
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
		}

		void fill(VectorSpaceType val) 
		{
			std::fill(_coefs.begin(), _coefs.end(), val);
		}
		

		VectorSpaceType& operator[](std::size_t idx) { return _coefs[idx]; }
		const VectorSpaceType& operator[](std::size_t idx) const { return _coefs[idx]; }

		//f(t) -> VectorSpaceType. это тип коэффициентов
		VectorSpaceType operator()(double t) const;

		spline operator+(const spline& other) const;
		spline operator*(double val);

	private:
		
		std::vector<VectorSpaceType> _coefs;
		interval _border;
		std::size_t _grid_size;

	};

	template<typename VectorSpaceType, std::size_t degree>
	spline<VectorSpaceType, degree>::spline() :
		_coefs(4u + degree - 2u),
		_border({0., 1.}),
		_grid_size(4u) {}


	template<typename VectorSpaceType, std::size_t degree>
	spline<VectorSpaceType, degree>::spline(std::size_t grid_size, interval border) :
		_coefs(grid_size + degree - 2u),
		_border(border),
		_grid_size(grid_size){}

	template<typename VectorSpaceType, std::size_t degree>
	spline<VectorSpaceType, degree>::spline(const spline& f) : 
		_coefs(f._coefs),
		_border(f._border),
		_grid_size(f._grid_size) {}

	template<typename VectorSpaceType, std::size_t degree>
	VectorSpaceType spline<VectorSpaceType, degree>::operator()(double t) const
	{
		auto filter = [](double t)->double 
		{
			if (t < 0.) return 0.;
			if (t > 1.) return 1.;
			return t;
		};
		/*Возвращаемый результат. Аналог 0 в VectorSpaceType*/
		VectorSpaceType sum = 0. * _coefs.front();
		
		const int index = cardinal::calculate_relative_index(t, _border, _grid_size);
		const auto& [a, b] = _border;
		const double inv_step = _border.get_inverse_step(_grid_size);
		const double step = _border.get_step(_grid_size);
		const double x = filter((t - (a + index * step)) * inv_step);
		
		const std::vector<double> ksi_val = [x](int deg, int index, int grid_size)	{
			
			auto val = cardinal::bsplvb(x, deg);
			
			if (index >= 0 && index < grid_size)
				return val;
			else {
				int delta = (index < 0) ? (index) : (index - grid_size + 1);
				
				/*Если мы за носителем, возвращаем пустой вектор*/
				if (std::abs(delta) >= deg)
					return std::vector<double>();

				if(delta < 0)
					return std::vector<double>(val.begin() + std::abs(delta), val.end());
				else
					return std::vector<double>(val.begin(), val.end() - delta);
			}
		}(degree,index,_grid_size);

		/*Если индекс в диапозоне 0 <= index < grid_size 
		* тогда используем подмассив из _coefs размера degree */		

		auto c_begin = _coefs.begin() + index;
		auto c_end = _coefs.begin() + (index + (degree - 1));

		auto it_ksi = ksi_val.begin();
		for (auto it = c_begin; it != c_end; ++it, ++it_ksi) {
			sum += (*it_ksi) * (*it);
		}

		return sum;
	}

	template<typename VectorSpaceType, std::size_t degree>
	spline<VectorSpaceType, degree> spline<VectorSpaceType, degree>::operator+(const spline& other) const 
	{
		spline<VectorSpaceType, degree> f(_grid_size, _border);

		for (int i = 0; i < other.size(); i++) {
			f[i] = _coefs[i] + other._coefs[i];
		}

		return std::move(f);
	}


}

