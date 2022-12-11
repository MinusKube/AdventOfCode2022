#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "day.h"

static void run(std::ifstream& file) {
	int total_signal_strength = 0;
	std::string screen = "\n";

	int cycle = 0;
	int register_value = 1;

	auto increase_cycle = [&] () {
		cycle += 1;

		if (cycle == 20 || (cycle - 20) % 40 == 0) {
			total_signal_strength += cycle * register_value;
		}

		int sprite_center_column = register_value + 1;
		int pixel_column = cycle % 40;

		screen += std::abs(sprite_center_column - pixel_column) <= 1 ? '#' : '.';
		
		if (pixel_column == 0) {
			screen += "\n";
		}
	};

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream stream(line);

		std::string operation;
		stream >> operation;

		if (operation == "noop") {
			increase_cycle();
		}
		else if (operation == "addx") {
			increase_cycle();
			increase_cycle();

			int value;
			stream >> value;

			register_value += value;
		}
	}

	print_p1_result(total_signal_strength);
	print_p2_result(screen);
}

static Day day(10, run);