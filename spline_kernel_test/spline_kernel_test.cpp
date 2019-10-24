#include <iostream>
#include "spline_kernel.h"
#include "interval.h"

int main()
{
	spl::interval interval(1.4, 1.0);
	spl::interval i = {0.0, 1.0};
	auto [a, b] = i;


	std::cout << a << " " << b << std::endl;
	std::cout << interval.length() << std::endl;

    std::cout << "Hello World! " << meaning_of_life() << std::endl;
}
