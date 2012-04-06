#include <iostream>
#include <numeric>
#include <set>
#include <map>
#include "euler.h"

const unsigned long factorial[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

template <typename T>
T factorial_sum(T n) {

	T sum = 0;
	while (n) {
		sum += factorial[n % 10];
		n /= 10;
	}
	return sum;
}

template <int limit>
bool is_chain(unsigned long term) {

	std::set<unsigned long> chain;
	chain.insert(term);

	while (1) {
		term = factorial_sum(term);
		if (chain.count(term)) {
			break;
		}
		chain.insert(term);
	};

	return (chain.size() == limit);
}

typedef std::map<unsigned long, std::set<unsigned long>> term_map_t;
typedef term_map_t::value_type term_pair_t;

unsigned int add_chains(unsigned int init, const term_pair_t& pair) {

	if (is_chain<60>(pair.first)) {
		init += pair.second.size();
	}
	return init;
}

int main() {

	term_map_t terms;

	for (unsigned long n = 1; n < 1000000; ++n) {
		const unsigned long sorted_n = euler::sort_digits_reverse(n);
		terms[sorted_n].insert(n);
	}

	std::cout << std::accumulate(terms.begin(), terms.end(), 0, add_chains) << std::endl;

	return 0;
}

