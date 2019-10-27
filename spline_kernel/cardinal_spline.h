#pragma once
#include <vector>
#include <assert.h>

#include "interval.h"

namespace sml::cardinal
{
	//функция - ступенька на отрезке [0,1]
	double rect(double t);

	//рекурсивное вычисление кардинального сплайна поряка k в точке t
	double ksi(double t, int k);

	//алгоритм основан на идеи де Бура из одноименной процедуры BSPLVB
	//t - из отрезка [0,1]
	//k - степень сплайна >= 1
	inline std::vector<double> bsplvb(double t, int k) 
	{
		assert(k >= 1);
		assert(interval(0.0, 1.0).is_contains(t));			
		
		auto deboor = [](double x, double ksi_l, double ksi_r, int degree)->double 
		{
			double inv_k_dec = 1.0 / ((double)degree - 1.0);
			return (x * inv_k_dec) * ksi_l + ((degree - x) * inv_k_dec) * ksi_r;
		};
		//начмнаем расчет
		std::vector<double> ksi = {0.0, 1.0, 0.0};
		
		for (int degree = 1; degree < k; degree++) 
		{
			std::vector<double> new_ksi((degree + 1) + 2);

			for (int i = 1; i < degree + 2; i++)
				new_ksi[i] = deboor(t + (degree + 1 - i), ksi[i - 1], ksi[i], degree + 1);

			ksi = new_ksi;
		}

		std::vector<double> answer_ksi(ksi.begin() + 1, ksi.end() - 1);

		return answer_ksi;
	}


	void MATHLIBRARY_API api_bsplvb(double t, int k);
}