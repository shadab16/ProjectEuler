#include <iostream>
#include "euler.h"

using euler::prime_set;
using euler::prime_sieve;

int main() {

	const unsigned int limit = 100000000;
	const prime_set primes = build_prime_set(prime_sieve(limit));

	int count = 0;

	for (prime_set::const_iterator p1 = primes.begin(); p1 != primes.end(); ++p1) {
		if (*p1 * *p1 > limit) {
			break;
		}
		for (prime_set::const_iterator p2 = p1; p2 != primes.end(); ++p2) {
			if (*p1 * *p2 > limit) {
				break;
			}
			++count;
		}
	}

	std::cout << count << std::endl;

	return 0;
}

