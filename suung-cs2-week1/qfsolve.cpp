/**
 * @brief Solves the given quadratic equation.
 *
 * This function, given real coefficients A, B, C to the equation
 * A*x*x + B*x + C = 0, returns the real part of a solution to the
 * equation thus defined. Where two real solutions exist, the one
 * closer to positive infinity is chosen.
 *
 * @param a the quadratic coefficient.
 * @param b the linear coefficient.
 * @param c the constant coefficient.
 *
 * @return the real part of a solution to the defined quadratic equation,
 *         as described.
 */

#include <cmath>
#include <iostream>
using namespace std;

double qfsolve(double a, double b, double c) 
{
	double dis = sqrt(b*b - 4*a*c);
	
	if (dis >= 0) 
	{
		return (-b + dis) / 2*a;
	}  
	
	else 
	{
		return 0.0;
	}
}

int main(int argc, char ** argv)
{
	double t1 = qfsolve(1,2,1);
	double t2 = qfsolve(1,3,2);
	double t3 = qfsolve(1,1,1);
	double t4 = qfsolve(3,2,1);
	double t5 = qfsolve(1,5,5);

	cout << "input: " << endl;
	cout << "a = 1, b = 2, c = 1" << endl;
	cout << "output: " << t1 << endl;
	cout << endl;
	
	cout << "input: " << endl;
	cout << "a = 1, b = 3, c = 2" << endl;
	cout << "output: " << t2 << endl;
	cout << endl;

	cout << "input: " << endl;
	cout << "a = 1, b = 1, c = 1" << endl;
	cout << "output: " << t3 << endl;
	cout << endl;

	cout << "input: " << endl;
	cout << "a = 3, b = 2, c = 1" << endl;
	cout << "output: " << t4 << endl;
	cout << endl;

	cout << "input: " << endl;
	cout << "a = 1, b = 5, c = 5" << endl;
	cout << "output: " << t5 << endl;
	cout << endl;
	
	return 0;
}
