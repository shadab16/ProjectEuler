#include <iostream>

int main() {

	const unsigned int limit = 1000;
	unsigned long sum(0);

	for (unsigned int i = 3; i < limit; i += 3) {
		sum += i;
	}

	for (unsigned int i = 5; i < limit; i += 5) {
		if (i % 3 != 0) {
			sum += i;
		}
	}

	std::cout << sum << std::endl;

	return 0;
}

