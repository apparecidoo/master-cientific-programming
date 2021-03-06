#include <iostream>
#include <functional>
#include <time.h>
#include <random>
#include <mpi.h>
#include <omp.h>
#include <chrono>
#include <ctime>
#include <ratio>

#include "queue_dynamic.h"
#include "equations.h"
#include "custom_exception.h"
#include "integrate_range.h"

#ifndef NUMERIC_METHOD_H
#define NUMERIC_METHOD_H

#define IS_PARALLEL 1

using namespace std;
using namespace std::placeholders;
using namespace std::chrono;

class NumericMethod {

private:
	//double _a = 0; // first number of interval integration 
	//double _b = 1; // second number of interval integration
	double _base_derivate_value = 0.00000001; // minimum number to derivate

	int factorial(int n); // calculate factorial
	double df_dx_generic(std::function<double(double)>f, double x, int degrees); // calculate every derivative by degree
	double df_dx(std::function<double(double)>f, double x); // calculate first derivative
	double df_dx_2(std::function<double(double)>f, double x); // calculate second derivative
	double df_dx_3(std::function<double(double)>f, double x); // calculate third derivative
	double df_dx_4(std::function<double(double)>f, double x); // calculate fourth derivative

public:
	NumericMethod();
	~NumericMethod();

	static double gradient_descent_a(double x0, double beta, double epsilon); // calculate descent gradient of equation a (f(x) = x�, x� = 2)
	static double gradient_descent_b(double x0, double beta, double epsilon); // calculate descent gradient of equation b (f(x) = x� - 2x� + 2, x� = 2)

	double midpoint(std::function<double(double)>f, IntegrateRange<double> range); // calculate midpoint for equation of one variable
	double trapezoidal(std::function<double(double)>f, IntegrateRange<double> range); // calculate trapezoidal for equation of one variable
	double simpson(std::function<double(double)>f, IntegrateRange<double> range); // calculate simpson for equation of one variable
	double numeric_square_by_divisions(std::function<double(double)>f, IntegrateRange<double> range, std::function<double(std::function<double(double)>, IntegrateRange<double>)> numeric_method_func, int divisions); // calculate numeric square for equation of one variable, passing the method and number of divisions on integrate region
	double numeric_square_by_error_rate(std::function<double(double)>f, IntegrateRange<double> range, std::function<double(std::function<double(double)>, IntegrateRange<double>)> numeric_method_func, std::function<double(std::function<double(double)>, IntegrateRange<double>, int)> numeric_method_error_func, double error_rate); // calculate numeric square for equation of one variable, passing the method, method error and error rate maximum
	double monte_carlo_by_attempts(std::function<double(double)>f, IntegrateRange<double> range, int attempts); // calculate monte carlo for equation of one variable and receiving divisions number
	double monte_carlo_by_error_rate(std::function<double(double)>f, IntegrateRange<double> range, double error); // calculate monte carlo for equation of one variable and maximum error rate
	double monte_carlo_volume_by_attempts(std::function<double(double, double, double)>f, IntegrateRange<double>* ranges, int attempts); // calculate monte carlo for equation of three variable and receiving attempts number
	double monte_carlo_volume_error_rate(std::function<double(double, double, double)>f, IntegrateRange<double>* ranges, double error); // calculate monte carlo for equation of three variable and error rate maximum
	
	void monte_carlo_volume_by_attempts_distributed(std::function<double(double, double, double)>f, IntegrateRange<double>* ranges, int attempts); // calculate monte carlo for equation of three variable and receiving attempts number, using MPI
	void monte_carlo_by_attempts_distributed(std::function<double(double)>f, IntegrateRange<double> range, int attempts); // calculate monte carlo for equation of one variable and receiving divisions number, using MPI
	double numeric_square_by_divisions_distributed(std::function<double(double)>f, IntegrateRange<double> range, std::function<double(std::function<double(double)>, IntegrateRange<double>)> numeric_method_func, int divisions); // calculate numeric square for equation of one variable, passing the method and number of divisions on integrate region, using OPEN MP
	double numeric_square_by_error_rate_distributed(std::function<double(double)>f, IntegrateRange<double> range, std::function<double(std::function<double(double)>, IntegrateRange<double>)> numeric_method_func, std::function<double(std::function<double(double)>, IntegrateRange<double>, int)> numeric_method_error_func, double error_rate); // calculate numeric square for equation of one variable, passing the method, method error and error rate maximum, using OPEN MP

	double midpoint_error(std::function<double(double)>f, IntegrateRange<double> range, int divisions); // calculate midpoint error for equation of one variable and receiving divisions number
	double trapezoidal_error(std::function<double(double)>f, IntegrateRange<double> range, int divisions); // calculate trapezoidal error for equation of one variable and receiving divisions number
	double simpson_error(std::function<double(double)>f, IntegrateRange<double> range, int divisions); // calculate simpson error for equation of one variable and receiving divisions number
	double monte_carlo_error(std::function<double(double)>f, IntegrateRange<double> range, int attempts); // calculate monte carlo error for equation of one variable and receiving attempts number
	double monte_carlo_volume_error(std::function<double(double, double, double)>f, IntegrateRange<double>* ranges, int attempts); // calculate monte carlo error for equation of three variable and receiving attempts number

	void test_gradient(); // test for gradient
	void test_numeric_square(); // test for numeric square
	void test_monte_carlo(); // test for monte carlo
	void test_monte_carlo_distributed(); // test for monte carlo using MPI
	void test_numeric_square_distributed(); // test for numeric square using OPEN MP
};

#endif
