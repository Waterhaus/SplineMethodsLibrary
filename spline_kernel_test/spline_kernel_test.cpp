#include <iostream>
#include <fstream>
#include <string>
#include "spline_kernel.h"
#include "interval.h"
#include "cardinal_spline.h"
#include "spline.h"
using namespace std;
using namespace sml;


template<typename T>
void SaveFunctionToFile(T f, sml::interval interval, int grid_size, string path) 
{
	const auto [a, b] = interval;

	ofstream myfile(path + "\\example.txt");
	if (myfile.is_open())
	{
		
		for (int i = 0; i < grid_size; i++)
		{
			auto x = a + i * interval.get_step(grid_size);
			auto y = f(x);
			myfile << x << " " << y << std::endl;
		}


		myfile.close();
	}
	else cout << "Unable to open file";
}



int main()
{

	sml::interval interval(1.4, 1.0);
	sml::interval i = {0.0, 1.0};
	auto [a, b] = i;


	std::cout << a << " " << b << std::endl;
	std::cout << interval.length() << std::endl;

    std::cout << "Hello World! " << meaning_of_life() << std::endl;

	sml::cardinal::api_bsplvb(0.25, 3);

	sml::spline<double, 4u> f(5u, { 0., 1. }), g(5u, { 0., 1. });
	f.fill(1.);
	g.fill(2.);

	

	auto h = 10. * f * 7.;
	h(-0.51);

	SaveFunctionToFile(h, { -1., 2. }, 100, "C:\\TXT");

}
