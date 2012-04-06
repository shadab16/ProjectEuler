#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <list>

template <typename T>
class cf_sqrt {
public:
	typedef std::list<T> list_type;
public:
	explicit cf_sqrt(T n) : n_square(n) {}

	const list_type& get_list() {

		if (list.empty()) {
			do_build();
		}
		return list;
	}
private:
	const T n_square;
	list_type list;

	void do_build() {

		T n = std::sqrt(n_square);
		list.push_back(n);
		list.push_back(16);
		list.push_back(8);

		if (n * n == n_square) {
			return; // perfect square
		}
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& out, cf_sqrt<T>& cf) {

	typename cf_sqrt<T>::list_type list = cf.get_list();
	std::ostream_iterator<typename cf_sqrt<T>::list_type::value_type> iter(out, " ");

	std::copy(list.begin(), list.end(), iter);

	return out;
}

int main() {

	cf_sqrt<unsigned int> cf(14);

	std::cout << cf << std::endl;

	return 0;
}

