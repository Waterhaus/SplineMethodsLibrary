#pragma once
#include <vector>

namespace spl::cardinal
{
	//������� - ��������� �� ������� [0,1]
	double rect(double t);

	//����������� ���������� ������������� ������� ������ k � ����� t
	double ksi(double t, int k);
}