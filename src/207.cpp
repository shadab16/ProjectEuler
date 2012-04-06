#include <iostream>
#include <cmath>

int main() {

	long perfect = 0;
	long imperfect = 0;

	long a = 1;

	do {
		++a;
		if (std::pow(2, std::floor(std::log(a) / std::log(2))) == a) {
			++perfect;
		} else {
			++imperfect;
		}
	} while (perfect * 12344 >= imperfect);

	std::cout << ((long long) a * (a - 1)) << std::endl;

	return 0;
}

/*

4^t = 2^t + k
(2^t)^2 - 2^t - k = 0

Let x = 2^t

x^2 - x - k = 0

Let k = a.b, where a-b = 1

x^2 - x - a.b = 0
x^2 - 1.x - a.b = 0
x^2 - (a-b).x - a.b = 0
x^2 - ax + bx - a.b = 0
x(x - a) + b(x - a) = 0
(x + b) (x - a) = 0

x = {a, -b}

Discard Case 1 
-b = 2^t

Case 2
a = 2^t
log2(a) = log2(2^t)
log2(a) = t.log2(2)
log2(a) = t

t = log2(a)


12345 * c[perfect] >= c[perfect] + c[imperfect]
12345 >= (c[perfect] + c[imperfect]) / c[perfect]
12345 >= (c[perfect] / c[perfect]) + (c[imperfect]) / c[perfect])
12345 >= 1 + (c[imperfect] / c[perfect])
12345 - 1 >= c[imperfect] / c[perfect]
12344 >= c[imperfect] / c[perfect]
c[perfect] * 12344 >= c[imperfect]

*/

