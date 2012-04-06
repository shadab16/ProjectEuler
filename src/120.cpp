#include <iostream>

int main() {

	unsigned long r_sum = 0;

	for (unsigned long a = 3; a <= 1000; ++a) {
		if (a % 2 == 0) {
			r_sum += a * (a - 2);
		} else {
			r_sum += a * (a - 1);
		}
	}

	std::cout << r_sum << std::endl;

	return 0;
}
