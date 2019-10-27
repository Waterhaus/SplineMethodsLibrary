#pragma once
#include <vector>
#include "interval.h"
#include "cardinal_spline.h"

namespace sml
{
	//VectorSpaceType - ���, �������������� �������� ���������� ������������ +,-,*, ��������� �� ����� � ��� �����
	//degree - ������� �������
	template<typename VectorSpaceType, std::size_t degree>
	class spline : final
	{
	public:
		spline() = delete;
		spline(std::vector<VectorSpaceType>&& coefs, interval border); //������������� �������� �����
		spline(std::size_t size, , interval border);//��������� ������. ������� ������ ������� size + degree - 2
		spline(const spline& f);

		~spline() {};

		//������� ���������� vector
		std::size_t size() { return _coefs.size() }

		VectorSpaceType& operator[](std::size_t idx) { return _coefs[idx]; }
		const VectorSpaceType& operator[](std::size_t idx) const { return _coefs[idx]; }

		//f(t) -> VectorSpaceType. ��� ��� �������������
		VectorSpaceType operator()(double t);

		spline operator+(const spline& lhs, const spline& rhs);
		spline operator*(double val);

	private:
		double ksi(double t) { return cardinal::ksi(t, degree) };

		std::vector<VectorSpaceType> _coefs;
		interval _border;
		double _step;

	};
}

