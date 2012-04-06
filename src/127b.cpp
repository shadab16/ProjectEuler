#include <iostream>
#include <vector>
#include "euler.h"

int main() {

	typedef unsigned long uint32;
	typedef std::vector<uint32> rad_t;

	const uint32 c_max = 120000;
	rad_t rad(c_max, 1);

	for (uint32 i = 2; i < c_max; ++i) {
		if (rad[i] != 1) {
			continue;
		}
		for (uint32 j = i; j < c_max; j += i) {
			rad[j] *= i;
		}
	}

	// Check triples

	uint32 sum = 0;

	for (uint32 c = 3; c < c_max; ++c) {

		for (uint32 a = 1; a * 2 < c; ++a) {
			if (rad[a] * rad[c-a] < c / rad[c] && euler::gcd(a, c-a) == 1) {
				sum += c;
			}
		}
	}

	std::cout << sum << std::endl;

	return 0;
}

