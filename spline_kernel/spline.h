#pragma once
#include <vector>

namespace spl 
{
	//VectorSpaceType - ���, �������������� �������� ���������� ������������ +,-,*...
	//degree - ������� �������
	template<typename VectorSpaceType, std::size_t degree>
	class spline
	{
	private:
		std::vector<VectorSpaceType> _coefs;
	};
}

