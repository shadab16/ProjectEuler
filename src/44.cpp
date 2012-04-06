#include <cmath>
#include <iostream>
#include <set>

template <typename T>
bool is_pentagonal(T pn) {

	double n = (1 + std::sqrt(1 + 24 * pn)) / 6;
	return (std::modf(n, &n) == 0.0);
}

template <typename T>
T sum_diff_pentagonal() {

	T diff(0), n(1);
	std::set<T> nums;

	while (!diff) {

		const T pn = (n * ((3 * n) - 1)) / 2;

		for (typename std::set<T>::const_iterator it = nums.begin(); it != nums.end(); ++it) {
			if (nums.count(pn - *it) && is_pentagonal(pn + *it)) {
				diff = pn - *it;
				break;
			}
		}

		nums.insert(pn);
		++n;
	}

	return diff;
}

int main() {

	std::cout << sum_diff_pentagonal<unsigned long>() << std::endl;

	return 0;
}

