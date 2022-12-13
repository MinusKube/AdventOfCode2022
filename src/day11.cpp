#include <algorithm>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "day.h"

struct Monkey {
	int id;
	std::vector<unsigned long long> items;
	char operation_sign;
	int operation_value;
	int divisible_value;
	int divisible_true_target;
	int divisible_false_target;
	int inspect_count = 0;
};

static void process_round(std::vector<Monkey>& monkeys, bool divide_worry) {
	int modulo_product = 1;
	for (size_t i = 0; i < monkeys.size(); i++) {
		modulo_product *= monkeys[i].divisible_value;
	}

	for (size_t i = 0; i < monkeys.size(); i++) {
		Monkey& monkey = monkeys[i];

		size_t monkey_item_count = monkey.items.size();
		for (size_t j = 0; j < monkey_item_count; j++) {
			unsigned long long item = monkey.items[j];

			int value = (monkey.operation_value == -1 ? item : monkey.operation_value);
			if (monkey.operation_sign == '*') {
				item *= value;
			}
			else {
				item += value;
			}

			if (divide_worry) {
				item /= 3;
			}
			else {
				item %= modulo_product;
			}

			int target_monkey = (item % monkey.divisible_value == 0)
				? monkey.divisible_true_target
				: monkey.divisible_false_target;
			monkeys[target_monkey].items.push_back(item);
			
			monkey.inspect_count += 1;
		}

		monkey.items.clear();
	}
}

static long long compute_inspect_counts_for_rounds(std::vector<Monkey>& monkeys, int round_count, bool divide_worry) {
	for (int i = 0; i < round_count; i++) {
		process_round(monkeys, divide_worry);
	}

	std::vector<long long> inspect_counts;
	for (size_t i = 0; i < monkeys.size(); i++) {
		inspect_counts.push_back(monkeys[i].inspect_count);
	}

	std::sort(inspect_counts.begin(), inspect_counts.end(), std::greater<>());

	if (inspect_counts.size() >= 2) {
		return inspect_counts[0] * inspect_counts[1];
	}

	throw std::invalid_argument("Can't compute inspect counts if there's only one monkey");
}

static void run(std::ifstream& file) {
	std::vector<Monkey> monkeys_p1;
	std::vector<Monkey> monkeys_p2;

	std::vector<std::string> lines;
	std::string temp_line;
	while (std::getline(file, temp_line)) {
		lines.push_back(temp_line);
	}

	std::vector<std::string>::iterator line_iter = lines.begin();
	while (line_iter < lines.end()) {
		Monkey monkey;

		auto match_next_line = [&line_iter] (const std::string& regex_str) -> std::smatch {
			std::regex regex(regex_str);
			std::smatch results;
			std::regex_match(*line_iter, results, regex);

			line_iter += 1;
			return results;
		};
		
		std::smatch id_results = match_next_line("^Monkey (\\d+):");
		monkey.id = std::stoi(id_results[1]);

		std::regex starting_items_regex("(\\d+)");
		std::sregex_iterator iter(
			(*line_iter).begin(),
			(*line_iter).end(),
			starting_items_regex
		);

		for (std::sregex_iterator last; iter != last; ++iter) {
			std::smatch results = *iter;

			monkey.items.push_back(std::stoi(results[1]));
		}

		line_iter += 1;

		std::smatch operation_results = match_next_line("^\\s+Operation: new = old (\\*|\\+) (\\w+)");
		std::smatch divisible_results = match_next_line("^\\s+Test: divisible by (\\d+)");
		std::smatch divisible_true_results = match_next_line("^\\s+If true: throw to monkey (\\d+)");
		std::smatch divisible_false_results = match_next_line("^\\s+If false: throw to monkey (\\d+)");

		monkey.operation_sign = operation_results[1].str().at(0);
		monkey.operation_value = (operation_results[2] == "old" ? -1 : std::stoi(operation_results[2]));
		monkey.divisible_value = std::stoi(divisible_results[1]);	
		monkey.divisible_true_target = std::stoi(divisible_true_results[1]);
		monkey.divisible_false_target = std::stoi(divisible_false_results[1]);

		line_iter += 1;

		monkeys_p1.push_back(monkey);
		monkeys_p2.push_back(monkey);
	}

	print_p1_result(compute_inspect_counts_for_rounds(monkeys_p1, 20, true));
	print_p2_result(compute_inspect_counts_for_rounds(monkeys_p2, 10000, false));
}

static Day day(11, run);