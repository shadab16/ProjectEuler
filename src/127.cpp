#include <algorithm>
#include <iostream>

int main() {

	const unsigned long c_max = 120000;
	unsigned long rad[c_max];

	// Build radicals

	std::fill_n(rad, c_max, 1);

	for (unsigned long i = 2; i < c_max; ++i) {
		if (rad[i] != 1) {
			continue;
		}
		for (unsigned long j = i; j < c_max; j += i) {
			rad[j] *= i;
		}
	}

	// Check a-b-c triples

	unsigned long sum(0);

	for (unsigned long c = 3; c < c_max; ++c) {
		if (rad[c] * 2 <= c && rad[c-1] * rad[c] < c) {
			sum += c;
		}
	}

	for (unsigned long c = 3; c < c_max; ++c) {
		if (rad[c] * 6 > c) {
			continue;
		}
		for (unsigned long a = 2; a * 2 < c; ++a) {
			unsigned long rad_abc = rad[a] * rad[c-a];

			if (rad_abc < c / rad[c]) {
				rad_abc *= rad[c];
				if (rad[rad_abc] == rad_abc) {
					sum += c;
				}
			}
		}
	}

	std::cout << sum << std::endl;

	return 0;
}

