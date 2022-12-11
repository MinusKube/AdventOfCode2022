#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "day.h"

struct Monkey {
	int id;
	std::vector<unsigned long long> items;
	bool operation_product;
	int operation_value;
	int divisible_value;
	int divisible_true_monkey;
	int divisible_false_monkey;
	int inspect_count = 0;
};

static void process_round(std::vector<Monkey>& monkeys, bool divide_worry) {
	int modulo_product = 1;
	for (size_t i = 0; i < monkeys.size(); i++) {
		modulo_product *= monkeys[i].divisible_value;
	}

	for (size_t i = 0; i < monkeys.size(); i++) {
		Monkey& monkey = monkeys[i];

		for (size_t j = 0; j < monkey.items.size(); j++) {
			unsigned long long item = monkey.items[j];

			if (monkey.operation_product) {
				item *= (monkey.operation_value == -1 ? item : monkey.operation_value);
			}
			else {
				item += (monkey.operation_value == -1 ? item : monkey.operation_value);
			}

			if (divide_worry) {
				item /= 3;
			}
			else {
				unsigned long long before = item;
				item %= modulo_product;

				if ((before % monkey.divisible_value == 0) !=
					(item % monkey.divisible_value == 0)) {
					std::cout << "NOP" << std::endl;
				}
			}

			if (item % monkey.divisible_value == 0) {
				monkeys[monkey.divisible_true_monkey].items.push_back(item);
			}
			else {
				monkeys[monkey.divisible_false_monkey].items.push_back(item);
			}

			monkey.inspect_count += 1;
		}

		monkey.items.clear();
	}
}

static void run(std::ifstream& file) {
	std::vector<Monkey> monkeys;
	std::vector<Monkey> monkeys2;

	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) {
			continue;
		}

		std::istringstream stream(line);

		Monkey monkey;

		std::string ignore;
		stream >> ignore >> monkey.id;

		std::getline(file, line);
		stream = std::istringstream(line);

		stream >> ignore >> ignore;
		while (!stream.eof()) {
			int item;
			stream >> item >> ignore;

			monkey.items.push_back(item);
		}

		std::getline(file, line);
		stream = std::istringstream(line);

		stream >> ignore >> ignore >> ignore >> ignore;

		char c;
		stream >> c;
		std::string val;
		stream >> val;

		monkey.operation_product = (c == '*');
		monkey.operation_value = (val == "old" ? -1 : std::stoi(val));

		std::getline(file, line);
		stream = std::istringstream(line);

		stream >> ignore >> ignore >> ignore;
		stream >> monkey.divisible_value;

		std::getline(file, line);
		stream = std::istringstream(line);

		stream >> ignore >> ignore >> ignore >> ignore >> ignore;
		stream >> monkey.divisible_true_monkey;

		std::getline(file, line);
		stream = std::istringstream(line);

		stream >> ignore >> ignore >> ignore >> ignore >> ignore;
		stream >> monkey.divisible_false_monkey;

		monkeys.push_back(monkey);
		monkeys2.push_back(monkey);
	}

	{
		for (int i = 0; i < 20; i++) {
			process_round(monkeys, true);
		}

		std::vector<int> inspect_counts;
		for (size_t i = 0; i < monkeys.size(); i++) {
			inspect_counts.push_back(monkeys[i].inspect_count);
		}

		std::sort(inspect_counts.begin(), inspect_counts.end(), std::greater<>());

		if (inspect_counts.size() >= 2) {
			print_p1_result(inspect_counts[0] * inspect_counts[1]);
		}
	}

	{
		for (int i = 0; i < 10000; i++) {
			process_round(monkeys2, false);
		}

		std::vector<int> inspect_counts;
		for (size_t i = 0; i < monkeys2.size(); i++) {
			inspect_counts.push_back(monkeys2[i].inspect_count);
			std::cout << monkeys2[i].inspect_count << std::endl;
		}

		std::sort(inspect_counts.begin(), inspect_counts.end(), std::greater<>());

		if (inspect_counts.size() >= 2) {
			print_p2_result(inspect_counts[0] * (long long) inspect_counts[1]);
		}
	}
}

static Day day(11, run);