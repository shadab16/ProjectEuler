#include <iostream>
#include "euler.h"

int main() {

	const unsigned long long target_r = 1e10;
	const euler::prime_set primes = euler::build_prime_set(euler::prime_sieve(250000));

	unsigned long long n = 1;

	for (euler::prime_set::const_iterator iter = primes.begin(); iter != primes.end(); ++iter, ++iter, n += 2) {
		const unsigned long long r = 2 * n * (*iter);
		if (r > target_r) {
			break;
		}
	}

	std::cout << n << std::endl;

	return 0;
}

