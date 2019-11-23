#pragma once
#include <vector>
#include <optional>
#include "interval.h"
#include "cardinal_spline.h"

namespace sml
{

	/*VectorSpaceType - тип, поддерживающий операции векторного пространства +,-, умножение на число 
	* degree - степень сплайна*/
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
		double _step;
		interval _domain;
		std::size_t _grid_size;

	};

	template<typename VectorSpaceType, std::size_t degree>
	spline<VectorSpaceType, degree>::spline() :
		_coefs(2u + degree),
		_border({0., 1.}),
		_step(_border.get_step(4)),
		_domain({ (-((int)degree - 1))* _step, 1. + ((int)degree - 1)*_step}),
		_grid_size(4u) {}


	template<typename VectorSpaceType, std::size_t degree>
	spline<VectorSpaceType, degree>::spline(std::size_t grid_size, interval border) :
		_coefs(grid_size + degree - 2u),
		_border(border),
		_step(_border.get_step(grid_size)),
		_domain({ (border._aborder + (1. - (double)degree)) * _step, border._bborder + ((double)degree - 1.)* _step }),
		_grid_size(grid_size){}

	template<typename VectorSpaceType, std::size_t degree>
	spline<VectorSpaceType, degree>::spline(const spline& f) : 
		_coefs(f._coefs),
		_border(f._border),
		_step(f._step),
		_domain(f._domain),
		_grid_size(f._grid_size) {}

	template<typename VectorSpaceType, std::size_t degree>
	VectorSpaceType spline<VectorSpaceType, degree>::operator()(double t) const
	{
		using std::vector;
		using std::optional;

		auto filter = [](double t)->double {
			if (t < 0.) return 0.;
			if (t > 1.) return 1.;
			return t;
		};

		/*Возвращаемый результат. Аналог 0 в VectorSpaceType*/
		VectorSpaceType sum = 0. * _coefs.front();
		if (!_domain.is_contains(t))
			return sum;
		
		const int index = cardinal::calculate_relative_index(t, _border, _grid_size);
		const auto& [a, b] = _border;
		const double inv_step = _border.get_inverse_step(_grid_size);
		const double step = _border.get_step(_grid_size);
		const double x = filter((t - (a + index * step)) * inv_step);
		
		const vector<double> ksi_val  = cardinal::bsplvb(x, degree);
		vector<optional<VectorSpaceType>> c(ksi_val.size());
	
		for(int k = index, i = 0; k < index + (int)c.size(); ++k, ++i){
			if (0 <= k && k < _coefs.size())
				c[i] = _coefs[k];
			else
				c[i] = std::nullopt;
		}

		for(int k = 0; k < c.size(); ++k){
			if (c[k].has_value())
				sum = sum + (ksi_val[k] * c[k].value());
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

