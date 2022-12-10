#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_set>

#include "day.h"

static void increase_cycle(int& cycle, int& x, int& p1, std::string& p2) {
	cycle += 1;

	if (cycle == 20 || (cycle - 20) % 40 == 0) {
		p1 += cycle * x;
	}

	if (std::abs((x + 1) - (cycle % 40)) <= 1) {
		p2 += "#";
	}
	else {
		p2 += ".";
	}

	if (cycle % 40 == 0) {
		p2 += "\n";
	}
}

static void run(std::ifstream& file) {
	int p1 = 0;
	std::string p2 = "\n";

	int cycle = 0;
	int x = 1;

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream stream(line);

		std::string operation;
		stream >> operation;

		if (operation == "noop") {
			increase_cycle(cycle, x, p1, p2);
		}
		else if (operation == "addx") {
			increase_cycle(cycle, x, p1, p2);
			increase_cycle(cycle, x, p1, p2);

			int value;
			stream >> value;

			x += value;
		}
	}

	print_p1_result(p1);
	print_p2_result(p2);
}

static Day day(10, run);