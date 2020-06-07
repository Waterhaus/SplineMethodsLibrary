#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>

#include "spline_kernel.h"
#include "interval.h"
#include "cardinal_spline.h"
#include "spline.h"
#include "generate_spline.h"
#include "data.h"
#include "classic_methods.h"
using namespace std;
using namespace spl;


template<typename T>
void SaveFunctionToFile(T f, spl::interval interval, int grid_size, string path) 
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





void test1()
{
	using spl::data::calculate_points;
	using spl::generator::create_spline;

	auto f = [](double t)->double {return t*t + 1.; };
	interval interv = { 0., 1. };
	auto sp_f = create_spline<double, 2u>(f, interv, 10);

	const auto points = calculate_points<double>(f, interv, 100);

	for (size_t i = 0; i < 100; i++)
	{
		std::cout << points[i] << ", ";
	}
}

void test2()
{
	const double root = std::sqrt(2.);
	auto f = [root](double t)->double {
		return std::pow(t - root, 3);
	};
	interval interv = { -10., 10. };
	
	auto answer = spl::numeric::bisection<double>(f, interv, 1e-6, 
		[](std::function<double(double)> func, interval gap)->bool {
		if (func(gap._aborder) * func(gap._bborder) < 0.)
			return true;
		return false;
		});

	if (answer)
		std::cout <<"bisection error = "<< std::abs(answer.value() - root) << std::endl;
}

int main()
{
	test2();
	test1();
	Eigen::Vector2f vec(0, 1);
	using spl::ker::spline;

	spl::interval interval(1.4, 1.0);
	spl::interval i = {0.0, 1.0};
	auto [a, b] = i;



	std::cout << a << " " << b << std::endl;
	std::cout << interval.length() << std::endl;

    std::cout << "Hello World! " << meaning_of_life() << std::endl;

	spl::cardinal::api_bsplvb(0.25, 3);

	const int size = 10;
	spl::ker::spline<double, 2u> f(size, { 0., 1. }), g(size, { 0., 1. });


	for (size_t i = 0; i < f.size(); i++)
	{
		f[i] = i + 1u;
	}

	auto h = f + g;

	std::cerr << "h(0.5) = " << h(0.5) << std::endl;
}
