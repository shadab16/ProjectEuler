#include <fstream>
#include <istream>
#include <ostream>
#include <iostream>
#include <sstream>
#include <string>
#include "psim.h"

namespace poker {

class hand {
	friend std::istream& operator >>(std::istream& in, hand& h);
	friend std::ostream& operator <<(std::ostream& out, const hand& h);
	friend bool operator >(const hand& left, const hand& right);
	friend bool operator <(const hand& left, const hand& right);
public:
	hand() : count(5) {}
private:
	const unsigned int count;
	std::string cards;
};

std::istream& operator >>(std::istream& in, hand& h) {

	std::ostringstream ostring;

	for (size_t i = 0; i < h.count; ++i) {
		char value, suit;
		in >> value >> suit;
		ostring << value << suit << ' ';
	}

	h.cards = ostring.str();

	return in;
}

std::ostream& operator <<(std::ostream& out, const hand& h) {

	return (out << h.cards);
}

bool operator >(const hand& left, const hand& right) {

	return (RankHand(left.cards.c_str()) > RankHand(right.cards.c_str()));
}

bool operator <(const hand& left, const hand& right) {

	return (right > left);
}

} // namespace poker

int main() {

	std::ifstream hands("resources/poker.txt");
	unsigned int count(0), wins(0);

	poker::hand player1;
	poker::hand player2;

	while (hands >> player1 >> player2) {
		if (player1 > player2) {
			++wins;
		}
		++count;
	}

	std::cout << wins << "/" << count << std::endl;

	return 0;
}

