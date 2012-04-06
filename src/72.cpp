#include <iostream>
#include <numeric>

int main() {

	const long limit = 1000000 + 1;

	// Totient sieve
	long totient[limit];

	for (long i = 0; i < limit; ++i) {
		totient[i] = i;
	}

	for (long i = 2; i < limit; ++i) {
		if (totient[i] == i) {
			for (long j = i; j < limit; j += i) {
				totient[j] = (totient[j] / i) * (i - 1);
			}
		}
	}

	// Length of Farey sequence
	long long length = 1;
	length = std::accumulate(&totient[1], &totient[limit - 1], length);

	// Not counting 0/n and n/n
	std::cout << (length - 2) << std::endl;

	return 0;
}

