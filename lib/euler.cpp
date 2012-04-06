#include <boost/dynamic_bitset.hpp>
#include <set>
#include "euler.h"

namespace euler {

prime_sieve::prime_sieve(prime_sieve::size_type upto) : limit(upto) {

	if (limit) {
		do_sieve();
	}
}

const prime_sieve::sieve_type& prime_sieve::get() const {

	return sieve;
}

void prime_sieve::do_sieve() {

	sieve.resize(limit, true);

	sieve[0] = 0;
	sieve[1] = 0;

	for (size_type i = 2; i * i < limit; ++i) {
		if (!sieve[i]) {
			continue;
		}
		for (size_type j = i; i * j < limit; ++j) {
			sieve[i * j] = 0;
		}
	}
}


prime_set build_prime_set(const prime_sieve& ps) {

	const prime_sieve::sieve_type sieve = ps.get();
	prime_set set;

	prime_sieve::size_type n = sieve.find_first();
	for (; n != prime_sieve::sieve_type::npos; n = sieve.find_next(n)) {
		set.insert(n);
	}

	return set;
}

} // euler

