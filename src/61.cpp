#include <algorithm>
#include <iterator>
#include <numeric>
#include <iostream>
#include <list>
#include <set>
#include <vector>
#include <cmath>

struct node;

typedef unsigned int element;
typedef std::set<element> figurate_set;
typedef std::list<element> cyclic_set;
typedef std::vector<cyclic_set> cyclic_sets;
typedef std::vector<node*>::iterator node_iterator;

struct node {
	const element value;
	const element prefix;
	const element suffix;
	std::set<node*> prev;
	std::set<node*> next;
	explicit node(element n) : value(n), prefix(n / 100), suffix(n % 100) {}
};

node* figurate_node(element number) {

	return new node(number);
}

void clear_figurate_node(node* node) {

	delete node;
}

std::vector<node*> build_nodes(const figurate_set& set) {

	std::vector<node*> nodes;
	std::transform(set.begin(), set.end(), std::back_inserter(nodes), figurate_node);

	for (node_iterator it = nodes.begin(); it != nodes.end(); ++it) {

		const element suffix = (*it)->suffix;
		for (node_iterator itp = nodes.begin(); itp != nodes.end(); ++itp) {
			if (*it == *itp) {
				continue;
			}
			if (suffix == (*itp)->prefix) {
				(*itp)->prev.insert(*it);
				(*it)->next.insert(*itp);
			}
		}

		const element prefix = (*it)->prefix;
		for (node_iterator its = nodes.begin(); its != nodes.end(); ++its) {
			if (*it == *its) {
				continue;
			}
			if ((*its)->suffix == prefix) {
				(*its)->next.insert(*it);
				(*it)->prev.insert(*its);
			}
		}
	}

	return nodes;
}

template <int length>
cyclic_sets find_all_cycles(const node* head, const node* current = 0) {

	if (!current) {
		current = head;
	}

	cyclic_sets cycles;
	const std::set<node*>& next = current->next;

	for (std::set<node*>::const_iterator it = next.begin(); it != next.end(); ++it) {
		cyclic_sets subs = find_all_cycles<length - 1>(head, *it);
		for (cyclic_sets::iterator sc = subs.begin(); sc != subs.end(); ++sc) {
			(*sc).push_front(current->value);
			cycles.push_back(*sc);
		}
	}

	return cycles;
}

template <>
cyclic_sets find_all_cycles<1>(const node* head, const node* current) {

	cyclic_sets cycles;

	if (current->suffix == head->prefix) {
		cyclic_set cycle;
		cycle.push_back(current->value);
		cycles.push_back(cycle);
	}

	return cycles;
}

cyclic_sets find_all_cycles(std::vector<node*>& nodes) {

	cyclic_sets all_cycles;

	for (node_iterator it = nodes.begin(); it != nodes.end(); ++it) {
		const cyclic_sets cycles = find_all_cycles<6>(*it);
		all_cycles.insert(all_cycles.end(), cycles.begin(), cycles.end());
	}

	return all_cycles;
}

bool is_figurate_cycle(const cyclic_set& cycle) {

	int figurates(0);

	for (cyclic_set::const_iterator it = cycle.begin(); it != cycle.end(); ++it) {

		double n(0);

		// Hex
		n = (std::sqrt(8 * (*it) + 1) + 1) / 4;
		if (std::floor(n) == n) {
			figurates |= (1 << 0);
			continue;
		}

		// Tri
		n = (std::sqrt(8 * (*it) + 1) - 1) / 2;
		if (std::floor(n) == n) {
			figurates |= (1 << 1);
			continue;
		}

		// Square
		n = std::sqrt(*it);
		if (std::floor(n) == n) {
			figurates |= (1 << 2);
			continue;
		}

		// Pent
		n = (std::sqrt(24 * (*it) + 1) + 1) / 6;
		if (std::floor(n) == n) {
			figurates |= (1 << 3);
			continue;
		}

		// Hept
		n = (std::sqrt(40 * (*it) + 9) + 3) / 10;
		if (std::floor(n) == n) {
			figurates |= (1 << 4);
			continue;
		}

		// Oct
		n = (std::sqrt(12 * (*it) + 4) + 2) / 6;
		if (std::floor(n) == n) {
			figurates |= (1 << 5);
			continue;
		}
	}

	return (figurates == 0x3F);
}

cyclic_set find_cycle(const figurate_set& set) {

	std::vector<node*> nodes = build_nodes(set);
	cyclic_sets cycles = find_all_cycles(nodes);

	std::for_each(nodes.begin(), nodes.end(), clear_figurate_node);

	return *std::find_if(cycles.begin(), cycles.end(), is_figurate_cycle);
}

int main() {

	figurate_set set;

	for (unsigned int n = 45; n <= 140; ++n) {
		set.insert((n * (n + 1)) / 2);
	}

	for (unsigned int n = 32; n <= 99; ++n) {
		set.insert(n * n);
	}

	for (unsigned int n = 26; n <= 81; ++n) {
		set.insert((n * (3*n - 1)) / 2);
	}

	for (unsigned int n = 21; n <= 63; ++n) {
		set.insert((n * (5*n - 3)) / 2);
	}

	for (unsigned int n = 19; n <= 58; ++n) {
		set.insert(n * (3*n - 2));
	}

	cyclic_set cycle = find_cycle(set);
	std::cout << std::accumulate(cycle.begin(), cycle.end(), 0) << std::endl;

	return 0;
}

