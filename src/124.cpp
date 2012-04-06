#include <iterator>
#include <iostream>
#include <map>
#include <vector>

typedef std::vector<unsigned long> rad_t;
typedef std::multimap<unsigned long, unsigned long> inv_rad_t;

int main() {

	const size_t limit = 100000 + 1;
	rad_t rad(limit, 1);

	for (size_t i = 2; i < limit; ++i) {
		if (rad[i] != 1) {
			continue;
		}
		for (size_t j = i; j < limit; j += i) {
			rad[j] *= i;
		}
	}

	inv_rad_t inverse;

	for (size_t i = 1; i < limit; ++i) {
		inverse.insert(std::make_pair(rad[i], i));
	}

	inv_rad_t::const_iterator it = inverse.begin();
	std::advance(it, 10000 - 1);

	std::cout << it->second << std::endl;

	return 0;
}

