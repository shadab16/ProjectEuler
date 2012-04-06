#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>

typedef std::list<long> palindromes;
typedef std::istream_iterator<long> ifile_iterator;

int main() {

	palindromes pal;

	std::ifstream file("resources/b002113_2.txt");
	std::copy(ifile_iterator(file), ifile_iterator(), std::back_inserter(pal));

	// sum := 0
	// for each palindrome k ∈ PAL

		

	return 0;
}

/*

P(n) = n(n+1)(2n+1) /6
     = (2.n^3 + 3.n^2 + n) / 6

Given a positive integer i, and
a positive palindromic integer k.

Find x, such that:

P(x) - P(i) = k

(2xxx + 3xx + x) / 6 - Pi = k
(2xxx + 3xx + x) / 6 = k + Pi
2xxx + 3xx + x = 6 (k + Pi)
2xxx + 3xx + x = 6k + 6Pi

Let m = 6k + 6Pi
2xxx + 3xx + x = m
2xxx + 3xx + x - m = 0

*/

