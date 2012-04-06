#include <iostream>
#include <map>

std::map<long, long> cache = {{0, 1}};

long partition(const long n) {

	if (n < 0) {
		return 0;
	}

	if (cache.count(n)) {
		return cache[n];
	}

	long sum = 0;
	for (long k = 1; k <= n; ++k) { 

		long terms = partition(n - (k * (3 * k - 1)) / 2) +
		             partition(n - (k * (3 * k + 1)) / 2);
		sum += (k % 2 == 0) ? -terms : terms;
	}

	return cache[n] = sum;
}

int main() {

	std::cout << (partition(100) - 1) << std::endl;
	return 0;
}

