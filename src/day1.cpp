#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "day.h"

static void run(std::ifstream& file) {
	std::vector<int> elf_calories;
	int current_calories = 0;

	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) {
			elf_calories.push_back(current_calories);
			current_calories = 0;
		}
		else {
			int calories = std::stoi(line);
			current_calories += calories;
		}
	}

	std::sort(elf_calories.begin(), elf_calories.end(), std::greater<int>());

	print_p1_result(elf_calories[0]);
	print_p2_result(elf_calories[0] + elf_calories[1] + elf_calories[2]);
}

static Day day(1, run);
