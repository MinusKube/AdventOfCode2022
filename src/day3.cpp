#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

#include "day.h"

constexpr int MAX_PRIORITY = 52;

static char getCharForPriority(int priority) {
	if (priority < 1 || priority > MAX_PRIORITY) {
		throw std::invalid_argument("Invalid priority: " + std::to_string(priority) + ". Must be within range [1-" + std::to_string(MAX_PRIORITY) + "]");
	}

	if (priority <= MAX_PRIORITY / 2) {
		return 'a' + (priority - 1);
	}
	else {
		return 'A' + (priority - MAX_PRIORITY / 2 - 1);
	}
}

static void run(std::ifstream& file) {
	std::vector<std::string> sacks;

	std::string line;
	while (std::getline(file, line)) {
		sacks.push_back(line);
	}

	size_t sack_count = sacks.size();

	// Part One
	int sum_p1 = 0;
	for (size_t i = 0; i < sack_count; i++) {
		const std::string& sack = sacks[i];

		std::string half_1 = sack.substr(0, sack.size() / 2);
		std::string half_2 = sack.substr(sack.size() / 2);

		for (int priority = 1; priority <= MAX_PRIORITY; priority++) {
			char c = getCharForPriority(priority);

			if (half_1.find(c) != std::string::npos &&
				half_2.find(c) != std::string::npos) {
				
				sum_p1 += priority;
			}
		}
	}

	// Part Two
	int sum_p2 = 0;
	for (size_t i = 0; i < sack_count; i += 3) {
		for (int priority = 1; priority <= MAX_PRIORITY; priority++) {
			char c = getCharForPriority(priority);

			if (sacks[i + 0].find(c) != std::string::npos &&
				sacks[i + 1].find(c) != std::string::npos &&
				sacks[i + 2].find(c) != std::string::npos) {
				
				sum_p2 += priority;
			}
		}
	}

	print_p1_result(sum_p1);
	print_p2_result(sum_p2);
}

static Day day(3, run);
