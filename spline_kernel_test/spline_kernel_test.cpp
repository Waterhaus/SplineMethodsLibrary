#include <iostream>
#include "spline_kernel.h"
#include "interval.h"
#include "cardinal_spline.h"
#include "spline.h"

int main()
{
	sml::interval interval(1.4, 1.0);
	sml::interval i = {0.0, 1.0};
	auto [a, b] = i;


	std::cout << a << " " << b << std::endl;
	std::cout << interval.length() << std::endl;

    std::cout << "Hello World! " << meaning_of_life() << std::endl;

	sml::cardinal::api_bsplvb(0.25, 3);
	//=========================
	std::vector<int> v(3u, 7);

	std::vector<int> w(v.begin()+4, v.end());
	//=========================

	sml::spline<double, 2u> f(5u, { 0., 1. }), g(5u, { 0., 1. });
	f.fill(1.);
	g.fill(2.);

	auto h = f + g;

	auto fx = h(0.5);

}
