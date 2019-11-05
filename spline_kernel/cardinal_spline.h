#pragma once
#include <vector>
#include <assert.h>
#include <cmath>

#include "interval.h"

namespace sml::cardinal
{
	/*������� - ��������� �� ������� [0,1]*/
	double rect(double t);

	/*����������� ���������� ������������� ������� ������ k � ����� t.*/
	double ksi(double t, int k);

	/* �������� ������� �� ���� �� ���� �� ����������� ��������� BSPLVB:
	 * t - �� ������� [0,1]
	 * k - ������� ������� >= 1*/
	inline std::vector<double> bsplvb(double t, int k) 
	{
		assert(k >= 1);
		assert(interval(0.0, 1.0).is_contains(t));			
		auto i = k - 1;
		auto deboor = [](double x, double ksi_l, double ksi_r, int degree)->double 
		{
			return 
				x * ksi_l
		/ //====================
			   (degree - 1)
		
		+	(degree - x) * ksi_r
		/ //====================
			   (degree - 1);
		};
		//�������� ������
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

	/*������� �� ���������, ���� � ����� ���������� ������ ������������ �� ������������ ������ 
	* ����:
	* ������������ ����� t .
	* �������� base_interval
	* �����: 
	* int index - ������ ������������ ������������ base_interval*/
	inline int calculate_relative_index(double t, interval base_interval, std::size_t grid_size) 
	{
		double inv_step = base_interval.get_inverse_step(grid_size);
		const auto& [a, b] = base_interval;
		return
			static_cast<int>(
				std::floor(
					(t - a) * inv_step
				));
	}

	void MATHLIBRARY_API api_bsplvb(double t, int k);
}