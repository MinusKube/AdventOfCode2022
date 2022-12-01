#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "day.h"

static void run(std::ifstream& file) {
	std::vector<int> sums;
	int current_sum = 0;

	std::string line;
	while (std::getline(file, line)) {
		if (line.empty()) {
			sums.push_back(current_sum);
			current_sum = 0;
		}
		else {
			int calories = std::stoi(line);
			current_sum += calories;
		}
	}

	std::sort(sums.begin(), sums.end(), std::greater<int>());

	std::cout << "Part One Result: " << sums[0] << std::endl;
	std::cout << "Part Two Result: " << (sums[0] + sums[1] + sums[2]) << std::endl;
}

Day day(1, run);
