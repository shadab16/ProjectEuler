#include <iostream>
#include <cmath>

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

int main(void) {

	const unsigned long long number = 600851475143ull;

	for (unsigned long i = std::sqrt(number); i > 2; --i) {
		if (number % i == 0 && is_prime(i)) {
			std::cout << i << std::endl;
			break;
		}
	}

	return 0;
}

