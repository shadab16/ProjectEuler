#include <algorithm>
#include <fstream>
#include <istream>
#include <ostream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <vector>

namespace poker {

class card {
	friend std::istream& operator >>(std::istream& in, card& c);
	friend std::ostream& operator <<(std::ostream& out, const card& c);
	friend bool operator >(const card& c1, const card& c2);
	friend bool operator <(const card& c1, const card& c2);
	friend bool operator >=(const card& c1, const card& c2);
	friend bool operator <=(const card& c1, const card& c2);
	friend bool operator ==(const card& c1, const card& c2);
	friend bool operator !=(const card& c1, const card& c2);
	template <int> friend class hand;
public:
	card();
	int strength() const;
private:
	char value;
	char suit;
	std::set<char> valid_values;
	std::set<char> valid_suits;
	std::map<char, int> value_map;
};

card::card() : value(0), suit(0) {

	const char values_[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
	valid_values.insert(values_, values_ + 13);

	const char suits_[] = {'C', 'D', 'H', 'S'};
	valid_suits.insert(suits_, suits_ + 4);

	for (size_t i = 0; i < 13; ++i) {
		value_map[values_[i]] = i + 2;
	}
}

int card::strength() const {

	if (!value) {
		return 0;
	}

	return value_map.find(value)->second;
}

std::istream& operator >>(std::istream& in, card& c) {

	in >> c.value;

	if (!c.valid_values.count(c.value)) {
		in.setstate(in.rdstate() | std::ios_base::failbit);
		c.value = 0;
	}

	in >> c.suit;

	if (!c.valid_suits.count(c.suit)) {
		in.setstate(in.rdstate() | std::ios_base::failbit);
		c.suit = 0;
	}

	return in;
}

std::ostream& operator <<(std::ostream& out, const card& c) {

	out << c.value << c.suit;
	return out;
}

bool operator >(const card& c1, const card& c2) {

	int val1(0), val2(0);
	std::map<char, int>::const_iterator iter;

	if ((iter = c1.value_map.find(c1.value)) != c1.value_map.end()) {
		val1 = iter->second;
	}

	if ((iter = c2.value_map.find(c2.value)) != c2.value_map.end()) {
		val2 = iter->second;
	}

	return (val1 > val2);
}

bool operator <(const card& c1, const card& c2) {

	return (c2 > c1);
}

bool operator >=(const card& c1, const card& c2) {

	return (c1 > c2) || (c1 == c2);
}

bool operator <=(const card& c1, const card& c2) {

	return (c1 < c2) || (c1 == c2);
}

bool operator ==(const card& c1, const card& c2) {

	return (c1.value == c2.value);
}

bool operator !=(const card& c1, const card& c2) {

	return !(c1 == c2);
}


template <int count>
class hand {
	template <int c> friend std::istream& operator >>(std::istream& in, hand<c>& h);
	template <int c> friend std::ostream& operator <<(std::ostream& out, const hand<c>& h);
	template <int c> friend bool operator >(const hand<c>& h1, const hand<c>& h2);
	template <int c> friend bool operator <(const hand<c>& h1, const hand<c>& h2);
private:
	typedef card card_type;
	typedef std::vector<card_type> card_container_type;

	card_container_type cards;
	card_container_type sortedcards;

	bool royal_flush() const;
	int straight_flush() const;
	int four_of_kind() const;
	int full_house() const;
	int flush() const;
	int straight() const;
	int three_of_kind() const;
	int two_pairs() const;
	int one_pair() const;
	const card_type& high_card() const;
};

template <int count>
bool hand<count>::royal_flush() const {

	const char suit = sortedcards[0].suit;

	for (int i = 0; i < count; ++i) {
		if (sortedcards[i].strength() != (i + 10) || sortedcards[i].suit != suit) {
			return false;
		}
	}

	return true;
}

template <int count>
int hand<count>::straight_flush() const {

	const char suit = sortedcards[0].suit;
	const int val = sortedcards[0].strength();

	for (int i = 0; i < count; ++i) {
		if (sortedcards[i].strength() != (i + val) || sortedcards[i].suit != suit) {
			return 0;
		}
	}

	return sortedcards[count - 1].strength();
}

template <int count>
int hand<count>::four_of_kind() const {

	int frq[15] = {0};

	for (size_t i = 0; i < count; ++i) {
		++frq[sortedcards[i].strength()];
	}

	for (size_t i = 0; i < count; ++i) {
		if (frq[i] == 4) {
			return i;
		}
	}

	return 0;
}

template <int count>
int hand<count>::full_house() const {

	int frq[15] = {0};
	size_t three_of_kind(0), pair(0);

	for (size_t i = 0; i < count; ++i) {
		++frq[sortedcards[i].strength()];
	}

	for (size_t i = 0; i < count; ++i) {
		if (frq[i] == 3) {
			three_of_kind = i;
		}
		if (frq[i] == 2) {
			pair = i;
		}
	}

	return (three_of_kind && pair) ? three_of_kind : 0;
}

template <int count>
int hand<count>::flush() const {

	std::map<char, int> map;

	for (size_t i = 0; i < count; ++i) {
		++map[sortedcards[i].suit];
	}

	return (map.size() == 1) ? sortedcards[count - 1].strength() : 0;
}

template <int count>
int hand<count>::straight() const {

	const int val = sortedcards[0].strength();

	for (int i = 0; i < count; ++i) {
		if (sortedcards[i].strength() != (i + val)) {
			return 0;
		}
	}

	return sortedcards[count - 1].strength();
}

template <int count>
int hand<count>::three_of_kind() const {

	int frq[15] = {0};

	for (size_t i = 0; i < count; ++i) {
		++frq[sortedcards[i].strength()];
	}

	for (size_t i = 0; i < count; ++i) {
		if (frq[i] == 3) {
			return i;
		}
	}

	return 0;
}

template <int count>
int hand<count>::two_pairs() const {

	int frq[15] = {0};
	size_t pairs(0), maxval(0);

	for (size_t i = 0; i < count; ++i) {
		++frq[sortedcards[i].strength()];
	}

	for (size_t i = 0; i < count; ++i) {
		if (frq[i] == 2) {
			++pairs;
			maxval = std::max(maxval, i);
		}
	}

	return (pairs == 2) ? maxval : 0;
}

template <int count>
int hand<count>::one_pair() const {

	int frq[15] = {0};

	for (size_t i = 0; i < count; ++i) {
		++frq[sortedcards[i].strength()];
	}

	for (size_t i = 0; i < count; ++i) {
		if (frq[i] == 2) {
			return i;
		}
	}

	return 0;
}

template <int count>
const typename hand<count>::card_type& hand<count>::high_card() const {

	return sortedcards[count - 1];
}

template <int count>
std::istream& operator >>(std::istream& in, hand<count>& h) {

	h.cards.clear();

	for (size_t i = 0; i < count; ++i) {
		typename hand<count>::card_type c;
		in >> c;
		h.cards.push_back(c);
	}

	h.sortedcards = h.cards;
	std::sort(h.sortedcards.begin(), h.sortedcards.end());

	return in;
}

template <int count>
std::ostream& operator <<(std::ostream& out, const hand<count>& h) {

	typedef typename hand<count>::card_type card_t;
	std::copy(h.cards.begin(), h.cards.end(), std::ostream_iterator<card_t>(out, " "));
	return out;
}

template <int count>
bool operator >(const hand<count>& h1, const hand<count>& h2) {

	if (h1.cards.size() != count || h2.cards.size() != count) {
		return false;
	}

	int value1(0), value2(0);

	value1 = h1.royal_flush();
	value2 = h2.royal_flush();

	if (value1 != value2) {
		return value1;
	}

	value1 = h1.straight_flush();
	value2 = h2.straight_flush();

	if (value1 != value2) {
		return (value1 > value2);
	}

	value1 = h1.four_of_kind();
	value2 = h2.four_of_kind();

	if (value1 != value2) {
		return (value1 > value2);
	} else if (value1 != 0) {
		return (h1.high_card() > h2.high_card());
	}

	value1 = h1.full_house();
	value2 = h2.full_house();

	if (value1 != value2) {
		return (value1 > value2);
	} else if (value1 != 0) {
		// Check the value of pair
		std::cerr << ":: Ambiguous : " << h1 << "\t" << h2 << std::endl;
	}

	value1 = h1.flush();
	value2 = h2.flush();

	if (value1 != value2) {
		return (value1 > value2);
	} else if (value1 != 0) {
		// Check the next highest cards
		std::cerr << ":: Ambiguous : " << h1 << "\t" << h2 << std::endl;
	}

	value1 = h1.straight();
	value2 = h2.straight();

	if (value1 != value2) {
		return (value1 > value2);
	}

	value1 = h1.three_of_kind();
	value2 = h2.three_of_kind();

	if (value1 != value2) {
		return (value1 > value2);
	} else if (value1 != 0) {
		// Check the next highest cards
		std::cerr << ":: Ambiguous : " << h1 << "\t" << h2 << std::endl;
	}

	value1 = h1.two_pairs();
	value2 = h2.two_pairs();

	if (value1 != value2) {
		return (value1 > value2);
	} else if (value1 != 0) {
		// Check the second pair
		std::cerr << ":: Ambiguous : " << h1 << "\t" << h2 << std::endl;
	}

	value1 = h1.one_pair();
	value2 = h2.one_pair();

	if (value1 != value2) {
		return (value1 > value2);
	} else if (value1 != 0) {
		// Check the next highest cards
		std::cerr << ":: Ambiguous : " << h1 << "\t" << h2 << std::endl;
	}

	return false; h1.high_card() > h2.high_card();
}

template <int count>
bool operator <(const hand<count>& h1, const hand<count>& h2) {

	return (h2 > h1);
}

} // namespace poker

int main() {

	std::ifstream hands("resources/poker.txt");
	unsigned int count(0), wins(0);

	poker::hand<5> player1;
	poker::hand<5> player2;

	while (hands >> player1 >> player2) {
		if (player1 > player2) {
			++wins;
		}
		++count;
	}

	std::cout << wins << "/" << count << std::endl;

	return 0;
}

