#ifndef EULER_H
#define EULER_H

#include <boost/dynamic_bitset.hpp>
#include <set>

namespace euler {

class prime_sieve {
public:
	typedef boost::dynamic_bitset<>::size_type size_type;
	typedef boost::dynamic_bitset<> sieve_type;

	explicit prime_sieve(size_type upto);
	const sieve_type& get() const;
private:
	void do_sieve();

	size_type limit;
	sieve_type sieve;
};


typedef std::set<prime_sieve::size_type> prime_set;

prime_set build_prime_set(const prime_sieve& ps);


template <typename T>
T sort_digits(T n) {

	unsigned int digits[10] = {0};

	for (; n; n /= 10) {
		++digits[n % 10];
	}

	for (unsigned int i = 0; i < 10; ++i) {
		while (digits[i]--) {
			n  = (n * 10) + i;
		}
	}

	return n;
}


template <typename T>
T sort_digits_reverse(T n) {

	unsigned int digits[10] = {0};

	for (; n; n /= 10) {
		++digits[n % 10];
	}

	for (int i = 9; i >= 0; --i) {
		while (digits[i]--) {
			n  = (n * 10) + i;
		}
	}

	return n;
}


template <typename T>
T reverse_digits(T n) {

	T reverse = 0;

	for (; n; n /= 10) {
		reverse = (reverse * 10) + (n % 10);
	}

	return reverse;
}

template <typename T>
T pow_mod(T base, T exp, T mod) {

	base = base % mod;
	T result(base);

	while (--exp > 0) {
		result = (result * base) % mod;
	}

	return result;
}

template <typename T>
bool is_prime(T n) {

	if (n < 2 || n % 2 == 0) {
		return false;
	}

	for (T i = 3; i * i < n; i += 2) {
		if (n % i == 0) {
			return false;
		}
	}

	return true;
}

template <typename T>
T gcd(T a, T b) {
	while (b) {
		const T temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

template <typename T>
T gcd(T a, T b, T c) {
	while (b) {
		const T temp = b;
		b = a % b;
		a = temp;
	}
	b = c;
	while (b) {
		const T temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

} // euler

#endif

