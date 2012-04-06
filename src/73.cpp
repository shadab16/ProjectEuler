#include <iostream>
#include "euler.h"

int main() {

	const long d_max = 12000;
	long count = 0;

	for (long d = 3; d <= d_max; ++d) {

		// Find n, such that n/d > 1/3
		long n = (d / 3) + 1;

		// Loop for n/d < 1/2
		while (2 * n < d) {
			if (euler::gcd(n, d) == 1) {
				++count;
			}
			++n;
		}
	}

	std::cout << count << std::endl;

	return 0;
}

