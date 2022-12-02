#include <iostream>
#include <string>

#include "day.h"

int main() {
	std::unordered_map<int, DayFunction>& day_functions = Day::get_day_functions();
	int day_count = day_functions.size();

	std::cout << "Welcome to Advent of Code 2022 by MinusKube!" << std::endl;
	std::cout << "Which day to you want to execute? (1-" << day_count << ")" << std::endl;

	int day;
	std::cin >> day;

	while (day < 1 || day > day_count) {
		std::cout << "Invalid day! (1-" << day_count << ")" << std::endl;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> day;
	}

	int example_char = std::cin.peek();
	bool example = (example_char == '?');

	std::string file_name;
	file_name += "../data/day";
	file_name += std::to_string(day);
	file_name += (example ? "_example.txt" : ".txt");

	std::ifstream file(file_name);

	if (file.is_open()) {
		std::cout << "Running day " << day << (example ? " example" : "") << " function..." << std::endl;
		std::cout << std::endl;

		try {
			day_functions[day](file);
		}
		catch (const std::exception& e) {
			std::cerr << "Error while running day " << day << (example ? " example" : "") << ": " << e.what() << std::endl;
		}
	}
	else {
		std::cout << "Error! Day file not found!" << std::endl;
	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;
}
