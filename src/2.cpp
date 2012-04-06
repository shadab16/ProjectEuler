#include <iostream>
#include <cmath>

unsigned long fibonacci(unsigned int n) {

	const double sqrt5 = std::sqrt(5);
	double fn =  (std::pow(1 + sqrt5, n) - std::pow(1 - sqrt5, n)) / (std::pow(2, n) * sqrt5);

	/* Reference: http://stackoverflow.com/questions/485525/round-for-float-in-c */
	fn = std::floor(fn + 0.5);

	return static_cast<unsigned long>(fn);
}

int main() {

	unsigned long long sum = 0;

	const unsigned long limit = 4000000;
	unsigned long fn = 0;

	for (unsigned int n = 1; fn < limit; ++n) {
		if (fn % 2 == 0) {
			sum += fn;
		}
		fn = fibonacci(n);
	}

	std::cout << sum << std::endl;

	return 0;
}

/*
	phi = (1 + sqrt5) / 2

	1 - phi
	= 1 - (1 + sqrt5) / 2
	= (2 - (1 + sqrt5)) / 2
	= (2 - 1 - sqrt5) / 2
	= (1 - sqrt5) / 2

	F(n)
	= ((1 + sqrt5) / 2) ^ n - ((1 - sqrt5) / 2) ^ n
	= (1 + sqrt5)^n / 2^n - (1 - sqrt5)^n / 2^n
	= [(1 + sqrt5)^n - (1 - sqrt5)^n] / [2^n * sqrt5]
*/


