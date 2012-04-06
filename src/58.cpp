#include <iostream>
#include "euler.h"

int main() {

	using euler::is_prime;

	unsigned long incr(2), primes(0), checked(1);

	for (unsigned long n = 1; !primes || primes * 10 >= checked; incr += 2) {

		// move to the first term of AP
		n += incr;

		// check next 3 terms for primality
		primes += is_prime(n) + is_prime(n + incr) + is_prime(n + (2 * incr));
		checked += 4;

		// set n to the last term of AP
		n += 3 * incr;
	}

	// The value of incr for which p/c evaluates to less than 10%
	// is (incr-2). As incr gives the common difference for terms
	// in the spiral, the side length is given by (incr+1).
	// Thus the target side length is: (incr-2+1) => (incr-1).

	std::cout << (incr - 1) << std::endl;

	return 0;
}

