#include <iostream>
#include <set>
#include "euler.h"

const long limit = 1e9;
const long B = 100;

typedef std::set<long> hamming_set;

int main() {

	const euler::prime_set primes = euler::build_prime_set(euler::prime_sieve(B + 1));

	hamming_set smooth;
	smooth.insert(1);

	long count = 0;

	while (!smooth.empty()) {

		count += smooth.size();
		hamming_set diff;

		for (euler::prime_set::const_iterator p = primes.begin(); p != primes.end(); ++p) {
			const long lim = limit / (*p);
			for (hamming_set::const_iterator s = smooth.begin(); s != smooth.end(); ++s) {
				if (*s > lim) {
					break;
				}
				const long n = (*p) * (*s);
				if (!smooth.count(n)) {
					diff.insert(n);
				}
			}
		}

		smooth.swap(diff);
	}

	std::cout << count << std::endl;

	return 0;
}

/*

#include <iostream>

const int primes[] = {97,89,83,79,73,71,67,61,59,53,47,43,41,37,31,29,23,19,17,13,11,7,5,3,2};
const long N = 1e9;

long H(const size_t p, const long long n) {

	if (n > N) {
		return 0;
	}

	if (p > 24) {
		return 1;
	}

	return H(p, primes[p] * n) + H(p + 1, n);
}

int main() {

	std::cout << H(0, 1) << std::endl;
	return 0;
}

*/

/*

Let pi be the i-th prime number, and
Hi(n) be its associated count of Hamming numbers up to n.

Then it follows:

H0(n)= (n ≥ 1) ? 1 : 0

Hi(n)= ∑k Hi-1(n/pi^k) 

*/
