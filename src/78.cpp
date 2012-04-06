#include <iostream>

const long limit   = 100000;
const long mod     = 1e6;
const long sign[2] = {-1, 1};

// Partition cache
long partition[limit] = {1};

int main() {

	long n = 0;
	while (++n < limit) {

		for (long k = 1; k <= n; ++k) {

			const long long p1 = (k * (3 * k - 1)) / 2;
			if (n - p1 < 0) {
				// n-p1 < 0, so p[n-p1] = 0
				// n-p1-k is also < 0, so p[n-(p1+k)] = 0
				break;
			}

			long terms = partition[n - p1];
			if (n - p1 - k >= 0) {
				terms += partition[n - p1 - k];
			}

			partition[n] += sign[k % 2] * terms;
		}

		partition[n] %= mod;

		if (partition[n] == 0) {
			std::cout << n << std::endl;
			break;
		}
	}

	return 0;
}

