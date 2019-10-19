#pragma once
#include <vector>

namespace spl 
{
	//VectorSpaceType - тип, поддерживающий операции векторного пространства +,-,*...
	//degree - степень сплайна
	template<typename VectorSpaceType, std::size_t degree>
	class spline
	{
	private:
		std::vector<VectorSpaceType> _coefs;
	};
}

