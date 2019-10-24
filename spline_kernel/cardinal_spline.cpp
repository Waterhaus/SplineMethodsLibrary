#include "pch.h"
#include "cardinal_spline.h"

namespace spl::cardinal 
{
	double rect(double t) 
	{
		if (t >= 0.0 && t < 1.0)
			return 1.0;
		else
			return 0.0;
	}

	double ksi(double t, int k)
	{
		if (k == 1)
			return rect(t);
		
		double inv_k_dec = 1.0 / ((double)k - 1.0);

		return (t * inv_k_dec) * ksi(t, k - 1) + ((k - t) * inv_k_dec) * ksi(t - 1.0, k - 1);
	}
}

